// c-modules/Sys.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Unix Standard library for system calls

// Sys.halt() - Stops the computer
void Sys_halt() {
    printf("\nSystem Halted.\n");
    // In Jack, halt is an infinite while(true) loop.
    // In a real OS, we tell the Kernel to kill our process.
    exit(0); 
}

// Sys.wait(duration) - Pauses execution
void Sys_wait(int duration) {
    // Jack waits in milliseconds. 
    // The Unix system call 'usleep' waits in microseconds (1 ms = 1000 us).
    usleep(duration * 1000); 
}

// Sys.error(errorCode)
void Sys_error(int errorCode) {
    printf("ERR%d\n", errorCode);
    Sys_halt();
}