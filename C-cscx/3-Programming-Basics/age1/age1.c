#include <stdio.h>

int main(void) {
    unsigned char age;
    char name[31];
    scanf("%30s", name);
    scanf("%hhu", &age);
    printf("%s is %u years old.\n", name, age);
}
