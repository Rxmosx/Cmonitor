#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mem.h"
#include "display.c"
#include "cpu.c"
#include "cpu.h"



int main() {
    cpuStat *cps_prev = malloc(sizeof(cpuStat));
    cpuStat *cps_curr = malloc(sizeof(cpuStat));
    memStats *mps = malloc(sizeof(memStats));
    char *model = cpu_model();

    read_cpu_stat(cps_prev);


    while (1) {
        sleep(2);

        read_mem_stat(mps);
        read_cpu_stat(cps_curr);

        double cpUsage = cpu_usage(cps_prev, cps_curr);
        double memUsage = mem_usage(mps);
        
        display_render(cpUsage, memUsage, model);

        *cps_prev = *cps_curr;
    }

    

    free(cps_prev);
    free(cps_curr);
    return 0;
}