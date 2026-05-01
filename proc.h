#ifndef PROC_H
#define PROC_H

#include "common.h"

int read_processes(ProcessInfo *list, int max_count);
int cmp_mem(const void *a, const void *b);
int check_processes();


#endif