#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (void) {
    int x1, y1, x2, y2;
    printf("Input x1: ");
    scanf("%d", &x1);
    printf("Input y1: ");
    scanf("%d", &y1);
    printf("Input x2: ");
    scanf("%d", &x2);
    printf("Input y2: ");
    scanf("%d", &y2);

    int delta_x = x2 - x1;
    int delta_y = y2 - y1;
    delta_x = delta_x * delta_x;
    delta_y = delta_y * delta_y;
    double exp = delta_x + delta_y;
    double result = sqrt(exp);
    printf("Distance between said points: %f\n", result);

    return EXIT_SUCCESS;
}
