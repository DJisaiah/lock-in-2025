# Chapter 2 Objects, Functions, and Types
Everything in C is either an *Object* type or *Function* type

- Both object types and function types have pointers
    - *a pointer is a memory address where the object/function is stored*
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

---
### Objects

An object is a place in storage during execution in which you can store values
- the type is relevant as different types interpret bit patterns differently

- To swap values you will need to make use of the Address-Of operator and the Indirection operator

- Objects have 4 storage durations
    1. Automatic
    2. Static
    3. Thread
    4. Allocated
