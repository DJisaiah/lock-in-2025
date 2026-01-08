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
