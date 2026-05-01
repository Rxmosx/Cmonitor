#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpu.h"
#include "proc.h"
#include "mem.h"
#include "display.h"


int main() {

    cpuStat *cps_prev = malloc(sizeof(cpuStat));
    cpuStat *cps_curr = malloc(sizeof(cpuStat));
    diskStat *disk_prev = malloc(sizeof(diskStat));
    diskStat *disk_curr = malloc(sizeof(diskStat));
    memStats *mps = malloc(sizeof(memStats));
    ProcessInfo *pi = malloc(sizeof(ProcessInfo) * 200);
    Uptime *up = malloc(sizeof(Uptime));
    char *model = cpu_model();

    read_cpu_stat(cps_prev);
    read_rate_disk(disk_prev);


    while (1) {
        setvbuf(stdout, NULL, _IONBF, 0);

        sleep(1);

        read_mem_stat(mps);
        read_cpu_stat(cps_curr);
        read_rate_disk(disk_curr);
        read_uptime(up);
        float temp = thermal_stat();

        double cpUsage = cpu_usage(cps_prev, cps_curr);
        double memUsage = mem_usage(mps);
        int procs = read_processes(pi, 200);
        long diff_r = disk_curr->read_sectors - disk_prev->read_sectors;
        long diff_w = disk_curr->write_sectors - disk_prev->write_sectors;
        double read_mb = (diff_r * 512.0) / (1024.0 * 1024.0);
        double write_mb = (diff_w * 512.0) / (1024.0 * 1024.0);
        
        display_render(cpUsage, memUsage, model, procs, pi, read_mb, write_mb, up, temp);

        *cps_prev = *cps_curr;
        *disk_prev = *disk_curr;
    }

    

    free(cps_prev);
    free(cps_curr);
    free(mps);
    free(pi);
    free(model);
    return 0;
}