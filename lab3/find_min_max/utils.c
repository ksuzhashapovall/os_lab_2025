#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *GenerateArray(size_t size) {
    int *array = malloc(size * sizeof(int));
    if (array == NULL) return NULL;
    
    srand(time(NULL));
    for (size_t i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
    return array;
}

void PrintArray(int *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}