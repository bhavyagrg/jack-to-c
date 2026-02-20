// c-modules/Math.c
#include <math.h> // Modern OS uses hardware math libraries

int Math_abs(int x) {
    return (x < 0) ? -x : x;
}

// In Jack, this was a complex 16-step bitwise loop.
// In C, the compiler translates '*' directly into a single hardware instruction (e.g., IMUL in x86).
int Math_multiply(int x, int y) {
    return x * y; 
}

// In Jack, this was a complex recursive function.
// In C, '/' triggers a hardware division circuit in the ALU.
int Math_divide(int x, int y) {
    if (y == 0) {
        // Sys.error(3);
        return 0; 
    }
    return x / y;
}

int Math_min(int x, int y) {
    return (x < y) ? x : y;
}

int Math_max(int x, int y) {
    return (x > y) ? x : y;
}