#include <stdlib.h>
#include <stdio.h>
#include "mem.h"


int read_mem_stat(memStats *s) {

    FILE *fp = fopen("/proc/meminfo", "r");

    if (!fp) return -1;

    fscanf(fp, "MemTotal: %ld kB\n", &s->total);
    fscanf(fp, "MemFree: %ld kB\n", &s->free);
    fscanf(fp, "MemAvailable: %ld kB\n", &s->available);
    fclose(fp);

    return 0;
}

double read_rate_disk(diskStat *st) {

    FILE *fp = fopen("/proc/diskstats", "r");
    char line[256];


    if (!fp) return -1;

    int found = 0;
    while (fgets(line, sizeof(line), fp)) {

        if (sscanf(line, " %*d %*d sda %*d %*d %ld %*d %*d %*d %ld", &st->read_sectors, &st->write_sectors) == 2) {
            found = 1;
            break;
        }

    }
    fclose(fp);
    return found;
}

double mem_usage(memStats *s) {

    long usage = s->total - s->free;
    s->usage = usage;

    return (s->total == 0) ? 0.0 : 100.0 * (s->total - s->available) / s->total;
}
