#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// ==========================================
// PART 1: THE SCREEN LIBRARY (Screen.jack equivalent)
// ==========================================

bool _color = true; // true = Black (Draw), false = White (Erase)

// 1. Initialize
void Screen_init() {
    _color = true;
    printf("\033[2J"); // Clear Console
}

// 2. Set Color (true=Black/Draw, false=White/Erase)
void Screen_setColor(bool b) {
    _color = b;
}

// 3. Draw Pixel (The Hardware Driver)
void Screen_drawPixel(int x, int y) {
    // Offset coordinates slightly so it looks centered
    int screen_x = x / 4 + 5; // Scaling down x slightly for terminal width
    int screen_y = y / 8 + 2; // Scaling down y for terminal height
    
    printf("\033[%d;%dH", screen_y, screen_x);

    if (_color) {
        printf("\033[47m \033[0m"); // White Block (Visible)
    } else {
        printf("\033[40m \033[0m"); // Black Block (Erased)
    }
}

// 4. Draw Horizontal Line
void Screen_drawHLine(int x1, int x2, int y) {
    int temp;
    if (x1 > x2) { temp = x1; x1 = x2; x2 = temp; }
    while (x1 <= x2) {
        Screen_drawPixel(x1, y);
        x1++;
    }
}

// 5. Draw Vertical Line
void Screen_drawVLine(int x, int y1, int y2) {
    int temp;
    if (y1 > y2) { temp = y1; y1 = y2; y2 = temp; }
    while (y1 <= y2) {
        Screen_drawPixel(x, y1);
        y1++;
    }
}

// 6. Draw Line (Bresenham's Algorithm - Same as Jack)
void Screen_drawLine(int x1, int y1, int x2, int y2) {
    int dx, dy, a, b, diff, temp;

    if (x1 > x2) {
        temp = x1; x1 = x2; x2 = temp;
        temp = y1; y1 = y2; y2 = temp;
    }

    dx = x2 - x1;
    dy = y2 - y1;
    a = 0; b = 0; diff = 0;

    if (dy == 0) { Screen_drawHLine(x1, x2, y1); return; }
    if (dx == 0) { Screen_drawVLine(x1, y1, y2); return; }

    if (dy > 0) {
        while ((a <= dx) && (b <= dy)) {
            Screen_drawPixel(x1 + a, y1 + b);
            if (diff < 0) { a++; diff += dy; }
            else          { b++; diff -= dx; }
        }
    } else {
        while ((a <= dx) && (b <= -dy)) {
            Screen_drawPixel(x1 + a, y1 - b);
            if (diff < 0) { a++; diff -= dy; }
            else          { b++; diff -= dx; }
        }
    }
}

// 7. Draw Rectangle
void Screen_drawRectangle(int x1, int y1, int x2, int y2) {
    while (y1 <= y2) {
        Screen_drawHLine(x1, x2, y1);
        y1++;
    }
}

// 8. Draw Circle
void Screen_drawCircle(int cx, int cy, int r) {
    int dy = -r;
    while (dy <= r) {
        int half_width = (int)sqrt(r*r - dy*dy);
        Screen_drawHLine(cx - half_width, cx + half_width, cy + dy);
        dy++;
    }
}

// ==========================================
// PART 2: THE MAIN APP (Main.jack equivalent)
// ==========================================

int main() {
    // 1. Init Screen
    Screen_init();

    // --- EXACT LOGIC FROM YOUR MAIN.JACK ---

    // 2. Draw House Body (Rectangle)
    // Jack: do Screen.setColor(true);
    Screen_setColor(true); 
    // Jack: do Screen.drawRectangle(200, 150, 300, 250);
    // Note: I scaled coordinates slightly to fit terminal
    Screen_drawRectangle(50, 50, 150, 150); 

    // 3. Draw Roof (Triangle/Lines)
    // Jack: do Screen.drawLine(200, 150, 250, 100);
    Screen_drawLine(50, 50, 100, 10);
    // Jack: do Screen.drawLine(300, 150, 250, 100);
    Screen_drawLine(150, 50, 100, 10);
    // Closing the roof bottom
    Screen_drawLine(50, 50, 150, 50);

    // 4. Draw Door (Erase Mode)
    // Jack: do Screen.setColor(false);
    Screen_setColor(false);
    // Jack: do Screen.drawRectangle(240, 200, 260, 250);
    Screen_drawRectangle(90, 100, 110, 150);

    // 5. Draw Sun (Bonus)
    Screen_setColor(true);
    Screen_drawCircle(180, 30, 15);

    // --- END OF MAIN.JACK LOGIC ---

    // Move cursor to bottom
    printf("\033[50;0H");
    printf("Jack House Logic running in C!\n");
    
    return 0;
}