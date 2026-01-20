// Write a C program that accepts two integers from the user and calculates the sum of the two integers.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int x, y;
    int result = scanf("%d %d", &x, &y);
    if (result == 2) {
        printf("%d\n", x + y);
    } else {
        puts("Invalid input.");
    }
    return EXIT_SUCCESS;
}
