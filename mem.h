typedef struct {
    long total, free, available, usage;
} memStats;

typedef struct {
    long read_sectors, write_sectors;
} diskStat;


int read_mem_stat(memStats *s);
double mem_usage(memStats *s);
double read_rate_disk(diskStat *st);