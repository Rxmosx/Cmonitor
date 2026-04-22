#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "proc.h"


int cmp_mem(const void *a, const void *b) {
    ProcessInfo *pa = (ProcessInfo *)a;
    ProcessInfo *pb = (ProcessInfo *)b;

    return pb->mem_kb - pa->mem_kb;
}



int read_processes(ProcessInfo *list, int max_count) {

    DIR *dir = opendir("/proc");
    struct dirent *entry;
    int count = 0;


    while ((entry = readdir(dir)) != NULL && count < max_count) {

        if (entry->d_name[0] < '0' || entry->d_name[0] > '9') {
            continue;
        }
        
        int pid = atoi(entry->d_name);
        char path[64];
        snprintf(path, sizeof(path), "/proc/%d/status", pid);

        FILE *f = fopen(path, "r");
        if (!f){
            continue;
        }

        memset(&list[count], 0, sizeof(ProcessInfo));

        ProcessInfo *p = &list[count];
        p->pid = pid;
        p->mem_kb = 0;

        char line[256];
        while (fgets(line, sizeof(line), f)) {
            

            if (strncmp(line, "Name:", 5) == 0) {
                sscanf(line, "Name:\t%[^\n]", p->name);

            } else if (strncmp(line, "State:", 6) == 0) {
                sscanf(line, "State:\t%c", &p->state);

            } else if (strncmp(line, "VmRSS:", 6) == 0) {
                sscanf(line, "VmRSS:\t%ld", &p->mem_kb);

            }

        }

        fclose(f);
        
        if (p->mem_kb > 0 && p->state == 'R') count++;
    }
    closedir(dir);

    return count;
}