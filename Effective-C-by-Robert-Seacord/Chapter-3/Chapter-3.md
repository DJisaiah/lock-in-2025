# Chapter 3 Arithmetic Types

- The two kinds of arithmetic types in C:
    - Integers
    - Floating-point
---
### Integers

#### Padding and Precision
- Padding refers to unused bits to accomodate hardware quirks or align with a given architecture
    - the point is to save cpu cycles.
        - Consider an architecture let's say a 32bit cpu where the cpu can read 4 bytes at a time. 
            - those 4 bytes are otherwise known as "one word"
            - note that padding behaviour depends on compiler* and can be defined
        - if we have two chars and an int in a struct
        - that means 1 + 1 + 4 bytes is necessary
        - but by the contigious nature of a struct when the cpu goes to read that block
        - there will be two bytes remaining of the int that the cpu hasnt read 
        - 1 + 1 + 2 (+2 to make 4)
        - this means we spend two whole cpu cycles just to read one int
        - whereas if we padded we wouldnt have this issue
            - the total bytes would then become 8
                - 1 byte char + 1 byte char + 2 bytes padding + 4 bytes int
    - *might be interesting to make sure i fully understand the logic behind different ordering of types in a struct affecting size*
- Width
    - the number of bits used to represent the value of a given type
        - excludes padding but includes sign
        - often denoted by $N$
- Precision
    - number of bits used to represent values
        - excludes sign and padding bits

#### <limits.h> header file
- the limits header file specifies the min/max/width of integer types for our use
    - it is determined by the compiler based on our architecture
        - instead of harcoded values being used it's smarter to adapt these values on arch (compiler developer)
        - if hardcoded code wouldn't port properly on different archs (64bit to 16bit)
            - programs could crash or behave unexpectedly in an effort to adapt
    - the C standard imposes 3 rules on this
        - not following them could lead to issues in our programs

#### Declaring Integers
- integer types are implictly declared signed unless prepended otherwise
    - except for char
        - C allows the compiler creator to decide whether char is signed or unsigned by default
    - compiler **must** treat it as signed otherwise

#### Unsigned Integers
- start at 0 and have larger ranges than their signed counterparts

##### Representation 
- quite easy to understand as it's represented in pure binary
    -   | Decimal | Binary | Hexadecimal |
        | :--- | :--- | :--- |
        | 10 | 0000 1010 | 0x0A |
        | 64 | 0100 0000 | 0x40 |
        | 127 | 0111 1111 | 0x7F |
        | 128 | 1000 0000 | 0x80 |
        | 200 | 1100 1000 | 0xC8 |
        | 240 | 1111 0000 | 0xF0 |
- range of types is $2^N - 1$
    - where N is the width

##### Wraparound
- this happens when you try to go beyond the width of the type
- in certain encryption algorithms this behaviour can actually be intentional
- it's important to be aware of this behaviour as in unsigned cases values can never be below 0

#### Signed Integers
- every unsigned int type has a signed counterpart that takes _the same space_
    - except `_Bool`

##### Representation
- C supports 3 different representation schemes
    - though the second is the most commonly used
    1. **Sign and magnitude**
    2. **Ones' compliment**
    3. **Two's compliment**
*todo*


