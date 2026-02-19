#include "JackOS.h"

int main() {
    Screen_clear();
    Output_printString("Hello from C-Jack!");
    Output_println();
    
    int *arr = Memory_alloc(10 * sizeof(int)); // Array of 10
    Output_printString("Allocated Memory Address: ");
    Output_printInt((long)arr);
    
    Sys_wait(2000); // Wait 2 seconds
    Sys_halt();
    return 0;
}