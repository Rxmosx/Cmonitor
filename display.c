#include <stdio.h>
#include "display.h"

void display_clear() {
    printf("/033[2J");
}

void display_move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void display_set_color(int bold, int color) {
    printf("\033[%d;%dm", bold ? 1 : 0, color);
}


void display_reset_color() {
    printf("\033[0m");
}

void display_bar(const char *label, double percent, int width) {
    int filled = (int)(percent / 100.0 * width);

    printf("%-6s [", label);  


    if (percent > 80.0)
        display_set_color(1, COLOR_RED);
    else if (percent > 50.0)
        display_set_color(1, COLOR_YELLOW);
    else
        display_set_color(1, COLOR_GREEN);

    for (int i = 0; i < width; i++) {
        if (i < filled)
            putchar('=');
        else if (i == filled)
            putchar('>');
        else
            putchar(' ');
    }

    display_reset_color();
    printf("] %5.1f%%\n", percent);
}

void display_render(double cpu, double mem_usage, char *model) {


    display_move_cursor(1, 1);


    display_set_color(1, COLOR_CYAN);
    printf("\t       === sysmon ===\n\n");
    display_reset_color();

    puts(model);
    display_bar("CPU", cpu, 30);
    display_bar("MEM", mem_usage, 30);
    


    fflush(stdout);
}