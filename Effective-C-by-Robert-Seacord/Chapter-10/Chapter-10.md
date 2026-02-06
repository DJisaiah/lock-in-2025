# Chapter 10 Program Structure
---

### Principles of Componentisation

---
### Structuring Programs

For a medium-to-large C project, the folder structure usually looks like this:

| Folder/File | Description |
| :--- | :--- |
| `src/` | Contains all `.c` source files (the logic). |
| `include/` | Contains all `.h` header files. |
| `lib/` | External libraries or pre-compiled binaries. |
| `build/` or `bin/` | Where the final executables end up. |
| `obj` |  Where the temporary object files go (`.o`) |
| `Makefile` | A script that tells the computer how to compile all these files together. |

example:

1. **`math_utils.h` (The Header)**
    - code
    ```c
    #ifndef MATH_UTILS_H // Header Guard (prevents double-loading)
    #define MATH_UTILS_H

    int add(int a, int b);

    #endif
    ```
    - it's possible for us to include something more than once especially since header files can be transitively included through other headers
        - this header guard is basically saying if math_utils.h is not already included, include it
    - recall
        - lines starting with `#` are for the preprocessor (preprocessor basically fills in the blanks in the early phase of compilation)
2. **`math_utils.c` (The Implementation)**
    - code
    ```c
    #include "math_utils.h"

    int add(int a, int b) {
        return a + b;
    }
    ```
    - we include math_utils header here as a best practice
        - the program would run just fine without it as the linker would find this definition and fill in the undefined gap in main
            - recall that the linker basically looks at a symbol table aiming to fill defined and undefined
        - if we didnt include the compiler would not warn us that we didn't actually keep our promise of actually doing the implementation
3. **`main.c` (The Entry Point)**
    - code
    ```c
    #include <stdio.h>
    #include "math_utils.h" // We "include" the header to use the add function

    int main() {
        printf("Total: %d", add(5, 10));
        return 0;
    }
    ```
    - `include`
        - recall that this basically copy-pastes the code of the header inside our C file
        - we're basically promising the compiler that hey the functions in that header exist trust us bro
