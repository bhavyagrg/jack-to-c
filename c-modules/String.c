// c-modules/String.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// To mimic Jack's OOP String, we define a struct (object).
typedef struct {
    char* buffer;
    int length;
    int max_length;
} JackString;

// String.new(maxLength)
JackString* String_new(int maxLength) {
    JackString* str = (JackString*)malloc(sizeof(JackString));
    str->max_length = maxLength;
    str->length = 0;
    // Allocate memory for the characters + 1 for the null terminator '\0'
    str->buffer = (char*)malloc((maxLength + 1) * sizeof(char)); 
    str->buffer[0] = '\0';
    return str;
}

// String.dispose()
void String_dispose(JackString* str) {
    free(str->buffer);
    free(str);
}

// String.appendChar(c)
void String_appendChar(JackString* str, char c) {
    if (str->length < str->max_length) {
        str->buffer[str->length] = c;
        str->length++;
        str->buffer[str->length] = '\0'; // Always cap it with null
    } else {
        printf("ERR17: String full\n");
    }
}