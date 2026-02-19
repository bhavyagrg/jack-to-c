#include <stdio.h>

static void draw_pixel(int x, int y, int r, int g, int b) {
    printf("\033[%d;%dH\033[48;2;%d;%d;%dm \033[0m", y, x, r, g, b);
}

int main(void) {
    printf("\033[2J");

    for (int i = 10; i < 20; i++) {
        draw_pixel(i, i, 255, 0, 0);
    }

    printf("\033[25;1H");
    return 0;
}
