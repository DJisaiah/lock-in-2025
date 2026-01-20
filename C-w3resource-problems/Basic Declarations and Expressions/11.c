// Write a C program that accepts two item's weight and number of purchases (floating point values) and calculates their average value.

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    float weight1, weight2;
    float count1, count2;

    puts("Enter weight of item 1");
    scanf("%f", &weight1);
    puts("Enter count of item 1");
    scanf("%f", &count1);

    puts("Enter weight of item 2");
    scanf("%f", &weight2);
    puts("Enter count of item 2");
    scanf("%f", &count2);
    
    float result = (weight1 * count1 + weight2 * count2) / (count1 + count2);
    printf("Average weight is %f\n", result);

    return EXIT_SUCCESS;
}
