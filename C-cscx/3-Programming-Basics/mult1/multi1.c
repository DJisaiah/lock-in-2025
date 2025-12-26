#include <stdio.h>

int main(void) {
    unsigned int x = 0, y = 0, z = 0; //pre-asign as there could be leftover data in that store
    scanf("%u %u %u", &x, &y, &z);
    printf("%u\n", x * y * z);
}
