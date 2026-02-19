#include <stdio.h>
#include <stdlib.h>

// ==========================================
// PART 1: THE SIMULATED HARDWARE
// ==========================================

// 32K words of simulated RAM
int RAM[32768]; 

// ==========================================
// PART 2: THE MEMORY OS LIBRARY
// ==========================================

int freeList;
int NO_BLOCK;

// We use #define for constants instead of "static int" for cleaner array indexing
#define FL_LENGTH 0
#define FL_NEXT 1
#define ALLOC_SIZE -1
#define NULL_PTR 0

// Forward declarations for helper functions
int Memory_best_fit(int size);
int Memory_do_alloc(int found_block, int size);
int Memory_find_prev_free(int object);

/** Initializes memory parameters. */
void Memory_init() {
    freeList = 2048;
    NO_BLOCK = 16384; 
    
    // Initial free block spans from 2048 to 16383
    RAM[freeList + FL_LENGTH] = 16384 - 2048;
    RAM[freeList + FL_NEXT] = NULL_PTR;
}

/** Returns the value of the main memory at the given address. */
int Memory_peek(int address) {
    return RAM[address];
}

/** Sets the value of the main memory at this address. */
void Memory_poke(int address, int value) {
    RAM[address] = value;
}

/** Find the block with the best fit */
int Memory_best_fit(int size) {
    int best_block = NO_BLOCK;
    int best_size = 16384 - 2048;
    int cur_block = freeList;
    int prev_block = NULL_PTR;
    
    while (cur_block != NULL_PTR) {
        int cur_size = RAM[cur_block + FL_LENGTH] - 1; 
        if (!(cur_size < size) && (cur_size < best_size)) {
            best_block = prev_block;
            best_size = cur_size;
        }
        prev_block = cur_block;
        cur_block = RAM[cur_block + FL_NEXT];
    }
    return best_block;
}

/** Allocate the found block and adjust free and alloc block headers */
int Memory_do_alloc(int found_block, int size) {
    int next_block;
    int block_size;
    
    if (RAM[found_block + FL_LENGTH] > (size + 1 + 2)) { 
        next_block = found_block + size + 1;
        RAM[next_block + FL_NEXT] = RAM[found_block + FL_NEXT];
        RAM[next_block + FL_LENGTH] = RAM[found_block + FL_LENGTH] - (next_block - found_block);
        found_block = found_block + 1;
        RAM[found_block + ALLOC_SIZE] = size + 1;
    } else {
        next_block = RAM[found_block + FL_NEXT];
        block_size = RAM[found_block + FL_LENGTH];
        found_block = found_block + 1;
        RAM[found_block + ALLOC_SIZE] = block_size;
    }
    return next_block;
}

/** Finds and allocates from the heap a memory block */
int Memory_alloc(int size) {
    int prev_block;
    int found_block;
    
    prev_block = Memory_best_fit(size);
    if (prev_block == NO_BLOCK) {
        found_block = NULL_PTR;
    } else {
        if (prev_block == NULL_PTR) {
            found_block = freeList;
            freeList = Memory_do_alloc(found_block, size);
        } else {
            found_block = RAM[prev_block + FL_NEXT];
            RAM[prev_block + FL_NEXT] = Memory_do_alloc(found_block, size);
        }
    }
    return found_block + 1;
}

int Memory_find_prev_free(int object) {
    int block;
    if (freeList > object) {
        return NULL_PTR;
    }
    block = freeList;
    while ((RAM[block + FL_NEXT] != NULL_PTR) && (RAM[block + FL_NEXT] < object)) {
        block = RAM[block + FL_NEXT];
    }
    return block;
}

/** De-allocates the given object and frees its space. */
void Memory_deAlloc(int object) {
    int alloc_size;
    int prev_block;
    int next_block;
    
    alloc_size = RAM[object + ALLOC_SIZE];
    object = object - 1; 
    prev_block = Memory_find_prev_free(object);
    
    if (prev_block == NULL_PTR) {
        RAM[object + FL_LENGTH] = alloc_size;
        RAM[object + FL_NEXT] = freeList;
        freeList = object;
        prev_block = object;
    } else {
        if ((prev_block + RAM[prev_block + FL_LENGTH]) == object) {
            RAM[prev_block + FL_LENGTH] = RAM[prev_block + FL_LENGTH] + alloc_size;
        } else {
            RAM[object + FL_LENGTH] = alloc_size;
            RAM[object + FL_NEXT] = RAM[prev_block + FL_NEXT];
            RAM[prev_block + FL_NEXT] = object;
            prev_block = object;
        }
    }
    
    if ((prev_block + RAM[prev_block + FL_LENGTH]) == RAM[prev_block + FL_NEXT]) {
        next_block = RAM[prev_block + FL_NEXT];
        RAM[prev_block + FL_LENGTH] = RAM[prev_block + FL_LENGTH] + RAM[next_block + FL_LENGTH];
        RAM[prev_block + FL_NEXT] = RAM[next_block + FL_NEXT];
    }
}

// ==========================================
// PART 3: MAIN TEST PROGRAM 
// ==========================================

int main() {
    // 1. Initialize the Heap
    Memory_init();
    printf("Memory Initialized. Heap starts at address 2048.\n\n");

    // 2. Allocate an array of size 5
    int array1 = Memory_alloc(5);
    printf("Allocated Array 1 (Size 5) at address: %d\n", array1);
    
    // 3. Allocate an array of size 10
    int array2 = Memory_alloc(10);
    printf("Allocated Array 2 (Size 10) at address: %d\n", array2);

    // 4. Test Peek and Poke
    Memory_poke(array1 + 0, 99); // Set first element
    printf("Stored 99 in Array 1. Peeked value: %d\n\n", Memory_peek(array1 + 0));

    // 5. Free Array 1
    printf("De-allocating Array 1...\n");
    Memory_deAlloc(array1);

    // 6. Allocate a new array of size 3
    // Because of your best-fit logic, it should reuse the space from array1!
    int array3 = Memory_alloc(3);
    printf("Allocated Array 3 (Size 3) at address: %d\n", array3);
    
    if (array3 == array1) {
        printf("\nSUCCESS: Array 3 reused the freed memory of Array 1!\n");
        printf("Your Jack defragmentation logic works perfectly in C.\n");
    }

    return 0;
}