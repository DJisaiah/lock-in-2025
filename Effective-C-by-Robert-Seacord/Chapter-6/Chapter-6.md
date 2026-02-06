# Chapter 6 Dynamically Allocated Memory
---

```
| Feature | `malloc` | `calloc` |
| :--- | :--- | :--- |
| **Full Name** | Memory Allocation | Contiguous Allocation |
| **Arguments** | 1: Total bytes to allocate | 2: Number of items, Size of each item |
| **Initialization** | Leaves memory **uninitialized** (contains "garbage" values) | **Zero-initializes** all bits in the allocated block |
| **Speed** | Faster (no overhead of clearing memory) | Slower (requires time to set bits to zero) |
```
- both `malloc` and `calloc` return a pointer to the first byte in the memory block
    - `malloc`
        - 
        ```c
            int *arr = malloc(10 * sizeof(int));
        ```
    - `calloc`
        - 
        ```c
            int *arr = calloc(10, sizeof(int));
        ```
    - be aware that doing ptr++ != moving to the next bit in memory but rather the next data-type specific byte in memory
        - table
        | If the pointer type is... | `ptr++` moves by... | (Commonly) |
        | :--- | :--- | :--- |
        | `char *ptr` | `1 * sizeof(char)` | **1 byte** |
        | `int *ptr` | `1 * sizeof(int)` | **4 bytes** |
        | `double *ptr` | `1 * sizeof(double)` | **8 bytes** |
        | `struct student_t *ptr` | `1 * sizeof(student_t)` | **XX bytes** (Size of struct) |
- regardless of which you use you still need to free the memory once ur done to avoid memory leaks
    - code example
    ```c
        free(arr);
        arr = NULL; // Good practice to prevent dangling pointers
    ```
