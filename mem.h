#include <stdlib.h>
#include <stdio.h>

typedef struct {
    long total, free, available, usage;
} memStats;

int read_mem_stat(memStats *s) {

    FILE *fp = fopen("/proc/meminfo", "r");

    if (!fp) return -1;

    fscanf(fp, "MemTotal: %ld kB\n", &s->total);
    fscanf(fp, "MemFree: %ld kB\n", &s->free);
    fscanf(fp, "MemAvailable: %ld kB\n", &s->available);
    fclose(fp);

    return 0;
}

double mem_usage(memStats *s) {

    long usage = s->total - s->free;
    s->usage = usage;

    return (s->total == 0) ? 0.0 : 100.0 * (s->total - s->available) / s->total;
}
