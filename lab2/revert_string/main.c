#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "revert_string.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string_to_revert>\n", argv[0]);
        return 1;
    }
    
    char *revert_str = malloc(strlen(argv[1]) + 1);
    strcpy(revert_str, argv[1]);
    
    printf("Original: %s\n", revert_str);
    RevertString(revert_str);
    printf("Reverted: %s\n", revert_str);
    
    free(revert_str);
    return 0;
}