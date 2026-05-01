#ifndef COMMON_H
#define COMMON_H 


typedef struct {
    long total, free, available, usage;
} memStats;

typedef struct {
    long read_sectors, write_sectors;
} diskStat;

typedef struct {
    long user, nice, system, idle, iowait, irq, softtirq;
} cpuStat;

typedef struct {
    int h, m, s;
} Uptime;

typedef struct {
    int pid;
    char name[256];
    char state;
    long mem_kb;
} ProcessInfo;

typedef struct {
    double cpu_usage;
    double mem_usage;
    float cpu_temp;
    char *cpu_model;
    int proc_count;
    ProcessInfo *procs;
    double disk_read_mb;
    double disk_write_mb;
    Uptime *uptime;
} SystemData;


#endif