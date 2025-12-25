#include <stdio.h>

int main(void) {
    int n;
    char s[31];
    scanf("%d", &n);
    scanf("%30s", s);
    printf("%s %d\n", s, n);
}
