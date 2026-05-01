#ifndef MEM_H
#define MEM_H

#include "common.h"

int read_mem_stat(memStats *s);
double mem_usage(memStats *s);
double read_rate_disk(diskStat *st);

#endif