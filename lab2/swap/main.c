#include <stdio.h>
#include "swap.h"

int main() {
    char a = 'a';
    char b = 'b';
    
    printf("Before swap: %c %c\n", a, b);
    Swap(&a, &b);
    printf("After swap: %c %c\n", a, b);
    
    return 0;
}