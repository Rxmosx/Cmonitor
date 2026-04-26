#ifndef PROC_H
#define PROC_H


typedef struct {
    int pid;
    char name[256];
    char state;
    long mem_kb;
} ProcessInfo;

int read_processes(ProcessInfo *list, int max_count);
int cmp_mem(const void *a, const void *b);


#endif