# Chapter 1 
---

#### The simple hello world
```C
#include <stdio.h> // std lib for io
#include <stdlib.h> // std lib for declarations for general utility funcs
int main(void) {
    puts("Hello world or bob"); // equivalent to print in python 
    // or printf("%s", msg)
    return EXIT_SUCCESS; // macro with a value of 0 from stdlib
    // there is an exit failure
}
```
hello.c

- Compilation happens through `cc {yourfile}.c`
    - you then get `a.out` file
    - `./a.out` to run
    - if you use the -o file flag you can specify your own file name for the compiled code
        - `cc -o hello hello.c`

- Do **not** allow users to specify their own format string when using printf as that results in vulnerabilities in your code. 
    - Certain format specifiers lead to vulnerabilities if used

- Beware that put prints a negative integer if there's an error and a non-negative otherwise
    - Whereas printf returns the number of characters printed if no errors, and otherwise a negative value
