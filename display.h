#ifndef DISPLAY_H
#define DISPLAY_H
#include "proc.h"
#include "cpu.h"

void display_clear();
void display_move_cursor(int row, int col);
void display_set_color(int bold, int color);
void display_reset_color();
void display_bar(const char *label, double percent, 
    int width, char *model);
void clean_model_name(char *dest, char *str);
void display_render(double cpu, double mem_usage, 
    char* model, int procs, 
    ProcessInfo *list, double read_disk, double write_disk, Uptime *up, float temp);
void display_processes(int procs, ProcessInfo *list);


#define COLOR_DEFAULT 0
#define COLOR_RED     31
#define COLOR_GREEN   32
#define COLOR_YELLOW  33
#define COLOR_CYAN    36
#define COLOR_WHITE   37

#endif