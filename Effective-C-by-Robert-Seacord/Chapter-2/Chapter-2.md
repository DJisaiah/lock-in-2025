# Chapter 2 Objects, Functions, and Types
Everything in C is either an *Object* type or *Function* type

- Both object types and function types have pointers
    - *a pointer is a memory address where the object/function is stored*
        - pointers can be indexed like arrays but this is really what's happening under the hood:
            - ```C
                int x = 1;
                // &x[1] is equivalent to *(&x + 1);
                ```
            - so when you do this you're accessing contigous stores in memory
    - pointers also have types but they are derived from the type of object called the referenced type

- C as a language uses pass-by-value
    - In other words you receive a copy of the value but not the original object itself to manipulate
    - To get past this you will use the following:
        1. The Address-Of operator (&)
            - This  **unary** operator generates a pointer to the operand
        2. The Indirection Operator (\*) (otherwise known as derefrencing operator)
            - This **unary** operator dereferences its operand (allows us to get the value of stored from the pointer)

- C has 4 types of scope
    1. File
        - object/function declared outside any block/parameter list
    2. Block
        - object/function declared inside any block/parameter list
    3. Function prototype
        - This one is interesting because in C the name you use in declaration (pure declaration and not definition) doesn't have to be the one you use in definition later on and so after you declare it, C 'forgets' the name you used in declaration
            - This is considered function prototype scope
                - think of it as a 'prototype'; not strictly meant to last long/be for final use
    4. Function
        - Accessible ANYWHERE inside the function it is defined in
        - **Labels are the only kind of identifier that has function scope**
            - think of the goto statements in batch files that allow you jump

* Scope is specific to identifiers and storage duration to objects

* Alignment refers to the restrictions a type may have on where objects of said type can be placed in memory
    - specifically the address
* Identifiers that start with "_{some upper case letter}" or "_{another underscore}" are reserved in C
    - the idea is that C committee might add sum more keywords with the same names or it could be used by another header file

---
### Objects

An object is a place in storage during execution in which you can store values
- the type is relevant as different types interpret bit patterns differently

- To swap values you will need to make use of the Address-Of operator and the Indirection operator

- Objects have 4 storage durations
    1. Automatic
        - Declared within a block or function parameter (only lives during that time)
    2. Static
        - Declared in file scope
            - Though variables in blocks can also be given static scope by being given the storage-class specifier `static` as in `static unsigned int`
        - Objects are initalised prior to program start-up but their identifiers are not
            - *this is why static objects must be initialised with a constant value and not a variable*
        - **Static objects are persist even beyond their scope** 
            - they stick around for the duration of the program
    3. Thread
        - concurrent programming*
    4. Allocated
        - dynamically allocated memory*

#### Types

- Booleans
    - ```C
        #include <stdbool.h>
        _Bool flag1 = 1; // old C style (doesnt need prep directive above)
        bool flag2 = true; // modern C. Equivalent to the above
        // bool is an alias for _Bool. true/false are just ints 1/0
        // bool and true/false both come from stdbool
        ```

- Character types
    - Types:
        1. `char`
        2. `signed char`
        3. `unsigned char`
        - These three types are incompaitible 
        - larger charset is `wchar_t` for int ppls
        - 2 and 3 can be used to store small ints (8 bits/1 byte) but not really advised unless specific case

- Integer types
    - Types:
        - | Type | Typical Size | Approximate Range | Notes |
            | :--- | :--- | :--- | :--- |
            | `signed char` | 8 bits | $-2^{7}$ to $2^{7} - 1$ ($-128$ to $127$) | Often just `char` |
            | `unsigned char` | 8 bits | $0$ to $2^{8} - 1$ ($0$ to $255$) | Used for small integers/bytes |
            | `short` | 16 bits | $-2^{15}$ to $2^{15} - 1$ ($-32,768$ to $32,767$) | Same as `short int` |
            | `unsigned short`| 16 bits | $0$ to $2^{16} - 1$ ($0$ to $65,535$) | |
            | `int` | 32 bits | $-2^{31}$ to $2^{31} - 1$ | Standard integer type |
            | `unsigned int` | 32 bits | $0$ to $2^{32} - 1$ | |
            | `long` | 32/64 bits | $-2^{31}$ to $2^{31} - 1$ (or higher) | Same as `long int` |
            | `long long` | 64 bits | $-2^{63}$ to $2^{63} - 1$ | Same as `long long int` |
            | `unsigned long long`| 64 bits | $0$ to $2^{64} - 1$ | |
        - except for `int` you can omit `int`

- enum types
    - let's you define a type that gives values to names
        - be it cardinals or months
            - `enum months { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };`
                - if you dont define the rest they automatically increment
                    - not specifying the first auto gives first = 0
    - **enums cant store anything other than ints**
        - whether this is signed (visual studio) or unsigned (gcc) is implementation dependent

- floating point types
    - | Type | Typical Size | Approximate Range (Magnitude) | Precision (Decimal Digits) |
        | :--- | :--- | :--- | :--- |
        | `float` | 32 bits | $1.2 * 10^{-38}$ to $3.4 * 10^{38}$ | ~6–9 digits |
        | `double` | 64 bits | $2.3 * 10^{-308}$ to $1.7 * 10^{308}$ | ~15–17 digits |
        | `long double` | 80/128 bits | $3.4 * 10^{-4932}$ to $1.1 * 10^{4932}$ | ~18–34 digits |

- void (cant hold any value)
    - use to indicate a function doesnt have a return type `void func(someparams)`
    - or use to indicate a function has no return types `myfunc(void)`

- function types
    - **The return type of a function cannot be an array type**
        1. When you declare an array inside a function
            - C adds that array and its metadata associated with the identifier for the array to its symbol table
                - that symbol table holds its size
                    - normally when you reference the identifier it decays to a pointer
                        - but when used with functions like `sizeof` it treats it as an Array Object
            - **The issue** when you return that array, you are returning the decayed pointer not the array object
                - the symbol table entry with the metadata is destroyed because the function is finished executing
                    - trying to return an array object wouldn't make sense because it'd be defying the array object's storage dj storage duration.
        2. The same process occurs for a static array (or one in file scope)

    - ```C
        int *myfunc(void) // returns a pointer to int
        int myfunc2() // works about the same as the above but is telling the compiler this func takes an unspecified number of args. You aren't protected by the compiler this way.
        ```

- Arrays
    - contigously allocated sequence of objects that all have the same type
        - 
        ```C
            int array1[17]; // int array with 17 elements
            int *array2[13]; // pointer to int array with 13 elements
            int array3[i][j]; // matrices can be formed nicely
        ```

* you can use `typedef` to create an alias for an existing type
    - also useful in treating non-types like types
        - helps in code reability

- structs
    - ancestor of classes
    - ```C
        struct somestruct {
            int somemember;
            int anothermember
        };

        struct somestruct examplestruct;       // Declare the object here
        struct somestruct *examplestruct_p;    // Declare the pointer here

        ```
        - shorthand:
            - ```C
                struct somestruct {
                    int somemember;
                } examplestruct, *examplestruct_p;
                ```
            - *the shorthand is useful for anonymous structs*
                - pointer arg at end is optional
    - can access members via dot operator (access to object)
        - if working with pointer can access with structure pointer operator (`->`)
    - each member is stacked one after the other in memory

- union
    - how this works:
        - when you declare a union, it reserves the largest type required memory
        - so even if you declare multiple members they still sit in that one memory address (start at it to be accurate)
    - generally used in cases where there are restrictions on memory
    - 
        ```C
            union Simple {
                int i;
                char c;
            };

            union Simple s;
            s.i = 65; // '65' is the ASCII code for 'A'
            printf("%c", s.c); // This will print 'A' because they share memory.
        ```
        - you could also put structs in unions but the principles still apply
        - when you overwrite a member, that member overwrites it's respective bits starting at that address

- tags
    - special naming mechanism for structs, unions, and enums
        - *the names of structs/unions/enums arent types and cannot alone be used to declare variables*
    - tags exist in a different namespace from regular identifiers
        - this implies you can have identifiers and tags with the same name
    - we can use typedef to define an alias for tags to treat them like types

### Type Qualifiers

*without these qualifiers, the type is considered unqualified*

- Types can be qualified with the following qualifiers:
    - const
        - objects declared with this type are not modifiable
            - there is a way around this if the original object was not const declared, and you const qualify a pointer to the object
                - cast back to regular pointer to int
    - volatile
        - signals to the compile that the value of a variable can change at any moment even if the program itself hasnt actually touched it
            - when addresses are connected to real-world devices/sensors
        - understanding why:
            - Modern C compilers are designed to be extremely "smart" and optimize your code to make it run faster.
            ```C
                int sensor = 10;
                while (sensor == 10) {
                    // do nothing, just wait for sensor to change
                }
            ```
            - The compiler looks at that and thinks: "Wait, nothing inside this loop changes 'sensor'. Therefore, it will stay 10 forever. I'll just optimize this into an infinite loop so I don't have to keep checking RAM".
            - if the sensor is actually some physical hardware, the compiler has just broken your program
        - "i must never cache this, always check new value in ram"
    - restrict
        - a promise to the compiler that there is no aliasing on this pointer
            - aliasing refers to having multiple pointers refer to the same point in memory
        - if this qualifier isnt passed the compiler will be scared to do heavy optimisations
            - heavy optimisations such as caching data in much faster cpu cache than ram
            - simply having two non-restricted pointers is enough chance for them to point to the same spot in memory
        - this is just a promise. if you break it the ownace is on you
            - garbage data and undefined behaviour
