# include <stdio.h>

void decrement(void) {
    static int count = 10; 
    // static gives us file scope
    // when re-run C ignores re-init even if value assigned in re-init
    // can use unsigned to save bit (if only keeping positive)
    // less bugs that way too when it comes to overflow
    count--;
    printf("%d\n", count);
}

int main(void) {
    for (int i = 0; i < 10; i++) {
        decrement();
    }
}
