// Write a C program that accepts three integers and finds the maximum of three.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int x, y, z;
    printf("Input the first integer: ");
    scanf("%d", &x);
    printf("Input the second integer: ");
    scanf("%d", &y);
    printf("Input the third integer: ");
    scanf("%d", &z);

    int max_int = (x > y) ? x : y;
    max_int = (max_int > z) ? max_int : z;

    printf("Maximum value of the three integers: %d\n", max_int);

    return EXIT_SUCCESS;
}
