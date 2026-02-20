// c-modules/Output.c
#include <stdio.h>

// Output.moveCursor(row, col)
void Output_moveCursor(int row, int col) {
    // ANSI escape code to move cursor (1-indexed, so we add 1)
    printf("\033[%d;%dH", row + 1, col + 1);
}

// Output.printChar(c)
void Output_printChar(char c) {
    putchar(c);
}

// Output.printString(s)
void Output_printString(const char* s) {
    // Streams the entire string buffer to the standard output
    printf("%s", s);
}

// Output.printInt(i)
void Output_printInt(int i) {
    printf("%d", i);
}

// Output.println()
void Output_println() {
    putchar('\n');
}