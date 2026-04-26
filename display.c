#include <stdio.h>
#include <string.h>
#include "display.h"
#include "proc.h"

void display_clear() {
    printf("\033[2J\033[3J\033[H");
    fflush(stdout);
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

void clean_model_name(char *dest, char *str) {
    char vendor[20], model[20];

    if (sscanf(str, "%[^(](R) Core(TM) %s", vendor, model) >= 2) {
        
        sprintf(dest, "%s %s", vendor, model);
    } else {
        strncpy(dest, str, 20);
    }
}

void display_bar(const char *label, double percent, int width, char *model) {
    int filled = (int)(percent / 100.0 * width);

    printf("%-6s [", label);  
    char dest[50];


    clean_model_name(dest, model);


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
    printf("] %5.1f%%", percent);

    if (strcmp(label, "MEM") != 0) {
        printf(" (%s)\n", dest);
    } else {
        printf("\n");
    }
}

void display_processes(int procs, ProcessInfo *list) {
    printf("\n");
    display_set_color(1, COLOR_CYAN);
    printf("%-6s %-20s %-10s %s\n", "PID", "NOME", "ESTADO", "MEM (MB)");
    display_reset_color();

    for (int i = 0; i < procs; i++) {
        ProcessInfo *p = &list[i];
        
        printf("%-6d %-20s ", p->pid, p->name);
        display_set_color(0, COLOR_WHITE);
        printf("%-10c ", p->state);
        display_reset_color();

        printf("%.1f\n", p->mem_kb / 1024.0);
        
    }
}

void display_render(double cpu, double mem_usage, char *model, int procs, 
    ProcessInfo *list, double read_disk, double write_disk) {

    fflush(stdout);
    display_clear();


    display_set_color(1, COLOR_CYAN);
    printf("\t       === CMONITOR v1.0 ===\n\n");
    display_reset_color();

    display_bar("CPU", cpu, 30, model);
    display_bar("MEM", mem_usage, 30, model);
    
    
    read_disk || write_disk > 1.0 ?     
        printf("Leitura: %.2f MB/s | Escrita: %.2f MB/s\n", read_disk, write_disk):
        printf("Leitura: %.2f KB/s | Escrita: %.2f KB/s\n", read_disk * 1024, write_disk * 1024)
    ;
    

    display_processes(procs, list);


    fflush(stdout);
}