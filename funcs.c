#include "proc.h"

void sort_procs(ProcessInfo *list, int start, int end) {

    if (start >= end) return ;

    long mid = list[(start + end) / 2].mem_kb;
    int i = start;
    int j = end;
    ProcessInfo aux;

    while (i <= j) {

        while (list[i].mem_kb > mid) {
            i++;
        }

        while (list[j].mem_kb < mid) {
            j--;
        }

        if (i <= j) {
            aux = list[i];
            list[i] = list[j];
            list[j] = aux;
            i++;
            j--;
        }
    }

    if (start < j) sort_procs(list, start, j);
    
    if (i < end) sort_procs(list, i, end);
    
}