// c-modules/Array.c
#include <stdlib.h>
#include <stdio.h>

// Array.new(size)
// In a real OS, this maps to asking the Kernel for contiguous memory.
int* Array_new(int size) {
    if (size <= 0) {
        printf("ERR2: Array size must be positive\n");
        exit(1);
    }
    // malloc dynamically allocates 'size' blocks of integers
    return (int*)malloc(size * sizeof(int));
}

// Array.dispose(arr)
// Gives the memory back to the Operating System's Free List.
void Array_dispose(int* arr) {
    if (arr != NULL) {
        free(arr);
    }
}