#include <stdio.h>

int main(void) {
    int user_input;
    while (scanf("%d", &user_input) == 1) {
        printf("%d\n", user_input);
    }
    return 0;
}
