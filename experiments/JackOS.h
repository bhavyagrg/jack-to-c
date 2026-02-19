#ifndef JACKOS_H
#define JACKOS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// --- Memory Module ---
#define Memory_alloc(size) malloc(size)
#define Memory_deAlloc(ptr) free(ptr)

// --- Output Module ---
#define Output_printString(s) printf("%s", s)
#define Output_printInt(i) printf("%d", i)
#define Output_println() printf("\n")

// --- Sys Module ---
#define Sys_wait(ms) usleep(ms * 1000)
#define Sys_halt() exit(0)

// --- Screen Module (Our Custom Driver) ---
void Screen_drawPixel(int x, int y) {
    printf("\033[%d;%dH*", y, x);
}
void Screen_clear() {
    printf("\033[2J");
}

#endif