#ifndef CPU_H
#define CPU_H

#include "common.h"

int read_cpu_stat(cpuStat *s);
double cpu_usage(cpuStat *prev, cpuStat *curr);
char *cpu_model();
int cpu_cores();
int read_uptime(Uptime *u);
float thermal_stat();





#endif