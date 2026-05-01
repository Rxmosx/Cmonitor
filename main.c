 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpu.h"
#include "funcs.h"
#include "proc.h"
#include "mem.h"
#include "common.h"
#include "display.h"


int main() {

    cpuStat *cps_prev = malloc(sizeof(cpuStat));
    cpuStat *cps_curr = malloc(sizeof(cpuStat));
    diskStat *disk_prev = malloc(sizeof(diskStat));
    diskStat *disk_curr = malloc(sizeof(diskStat));
    memStats *mps = malloc(sizeof(memStats));
    Uptime *up = malloc(sizeof(Uptime));

    SystemData *data = malloc(sizeof(SystemData));

    read_cpu_stat(cps_prev);
    read_rate_disk(disk_prev);
    data->cpu_model = cpu_model();


    data->proc_count = check_processes();
    data->procs = malloc(sizeof(ProcessInfo) * (data->proc_count + 5));

    while (1) {
        setvbuf(stdout, NULL, _IONBF, 0);

        sleep(1);


        read_mem_stat(mps);
        read_cpu_stat(cps_curr);
        read_rate_disk(disk_curr);
        read_uptime(up);
        data->uptime = up;
        data->cpu_temp = thermal_stat();

        int num_processes = check_processes();
        ProcessInfo *aux = realloc(data->procs, sizeof(ProcessInfo) * num_processes);

        if (aux) {

            data->procs = aux;
        } else {

            perror("Error to allocate memory");
            sleep(1);
            continue;
        }


        data->cpu_usage = cpu_usage(cps_prev, cps_curr);
        data->mem_usage = mem_usage(mps);
        data->proc_count = read_processes(data->procs, num_processes);

        long diff_r = disk_curr->read_sectors - disk_prev->read_sectors;
        long diff_w = disk_curr->write_sectors - disk_prev->write_sectors;
        data->disk_read_mb = (diff_r * 512.0) / (1024.0 * 1024.0);
        data->disk_write_mb = (diff_w * 512.0) / (1024.0 * 1024.0);
        
        sort_procs(data->procs, 0, num_processes - 1);

        display_render(data);


        *cps_prev = *cps_curr;
        *disk_prev = *disk_curr;

    }



    free(cps_prev);
    free(cps_curr);
    free(disk_prev);
    free(disk_curr);
    free(mps);
    free(up);
    free(data->procs);
    free(data);

    return 0;
} 