// c-modules/Keyboard.c
#include <stdio.h>

// Keyboard.readChar()
char Keyboard_readChar() {
    char c = getchar(); // Reads one keypress from the OS buffer
    return c;
}

// Keyboard.readLine(message)
void Keyboard_readLine(const char* message, char* buffer, int max_len) {
    printf("%s", message); // Print the prompt
    // Safely read a line from standard input (stdin)
    fgets(buffer, max_len, stdin); 
}

// Keyboard.readInt(message)
int Keyboard_readInt(const char* message) {
    int value;
    printf("%s", message);
    scanf("%d", &value); // Tells OS to parse the input as an integer
    return value;
}