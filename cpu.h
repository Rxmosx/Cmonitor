#ifndef CPU_H
#define CPU_H

typedef struct {
    long user, nice, system, idle, iowait, irq, softtirq;
} cpuStat;

int read_cpu_stat(cpuStat *s);
double cpu_usage(cpuStat *prev, cpuStat *curr);
char *cpu_model();
int cpu_cores();






#endif