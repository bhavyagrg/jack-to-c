#include <stdio.h>

// 1. The Basic "Pixel" Function (Your Tool)
void draw_pixel(int x, int y, int r, int g, int b) {
    // \033[y;xH moves cursor. \033[48... sets color. " " prints the pixel.
    printf("\033[%d;%dH\033[48;2;%d;%d;%dm \033[0m", y, x, r, g, b);
}

// 2. The Rectangle Function (The Logic)
// This works exactly like Screen.drawRectangle in Jack!
void draw_rectangle(int start_x, int start_y, int width, int height, int r, int g, int b) {
    
    // Loop through every Row (y)
    for (int y = start_y; y < start_y + height; y++) {
        
        // Loop through every Column (x) inside that row
        for (int x = start_x; x < start_x + width; x++) {
            
            // Draw the pixel at this specific (x, y)
            draw_pixel(x, y, r, g, b);
        }
    }
}

int main() {
    // Clear the screen first so it's clean
    printf("\033[2J");

    // Draw a RED Rectangle at (10, 5) size 20x10
    draw_rectangle(10, 5, 20, 10, 255, 0, 0);

    // Draw a BLUE Rectangle at (35, 10) size 15x8
    draw_rectangle(35, 10, 15, 8, 0, 0, 255);

    // Move cursor to bottom so prompt doesn't overwrite art
    printf("\033[30;0H"); 
    return 0;
}