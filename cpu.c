#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"



int read_cpu_stat(cpuStat *s) {

    FILE *fp = fopen("/proc/stat", "r");

    if (!fp) return -1;

    fscanf(fp, "cpu %ld %ld %ld %ld %ld %ld %ld",
           &s->user, &s->nice, &s->system, &s->idle, &s->iowait, &s->irq, &s->softtirq);
    fclose(fp);

    return 0;
}


double cpu_usage(cpuStat *prev, cpuStat *curr) {

    long prev_idle = prev->idle + prev->iowait;
    long curr_idle = curr->idle + curr->iowait;

    long prev_total = prev->user + prev->nice + prev->system + 
            prev->idle + prev->iowait + prev->irq + prev->softtirq;

    long curr_total = curr->user + curr->nice + curr->system +
            curr->idle + curr->iowait + curr->irq + curr->softtirq;

    long total_diff = curr_total - prev_total;
    long idle_diff = curr_idle - prev_idle;

    return (total_diff == 0) ? 0.0 : 100.0 * (total_diff - idle_diff) / total_diff;    
}


char *cpu_model() {

    static char model[256];
    FILE *fp = fopen("/proc/cpuinfo", "r");

    if (!fp) return NULL;

    while (fgets(model, sizeof(model), fp)) {

        if (sscanf(model, "model name : %[^\n]", model) == 1) {
            fclose(fp);
            return model;
        }
    }

    fclose(fp);
    return NULL;
}


int cpu_cores() {

    int cores = 0;
    char line[256];

    FILE *fp = fopen("/proc/cpuinfo", "r");

    if (!fp) return 0;

    while (fgets(line, sizeof(line), fp)) {

        if (sscanf(line, "cpu cores : %d", &cores) == 1) {
            fclose(fp);
            return cores;
        }
    }

    fclose(fp);
    return 0;
}
