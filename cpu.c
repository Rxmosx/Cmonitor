#include <stdio.h>
#include <stdlib.h>


typedef struct {
    long user, nice, system, idle, iowait, irq, softtirq;
} cpuStats;

int read_cpu_stat(cpuStats *s) {

    FILE *fp = fopen("/proc/stat", "r");

    if (!fp) return -1;

    fscanf(fp, "cpu %ld %ld %ld %ld %ld %ld %ld",
           &s->user, &s->nice, &s->system, &s->idle, &s->iowait, &s->irq, &s->softtirq);
    fclose(fp);
    return 0;

}


double cpu_usage(cpuStats *prev, cpuStats *curr) {

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
