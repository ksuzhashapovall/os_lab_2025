#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <array_size> <processes_count>\n", argv[0]);
        return 1;
    }

    int array_size = atoi(argv[1]);
    int processes_count = atoi(argv[2]);

    if (array_size <= 0 || processes_count <= 0) {
        printf("Error: array_size and processes_count must be positive\n");
        return 1;
    }

    int *array = GenerateArray(array_size);
    if (array == NULL) {
        printf("Error: memory allocation failed\n");
        return 1;
    }

    printf("Generated array:\n");
    PrintArray(array, array_size);

    struct MinMax min_max = GetMinMax(array, 0, array_size);
    
    printf("Min: %d\n", min_max.min);
    printf("Max: %d\n", min_max.max);

    free(array);
    return 0;
}