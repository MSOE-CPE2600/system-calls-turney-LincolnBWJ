/*
 * Lincoln Jiang
 * 11/1/2025
 * pinfo.c
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/resource.h>
#include <errno.h>

// Helper to convert scheduler number to string [cite: 58]
const char* get_sched_string(int sched) {
    switch (sched) {
        case SCHED_OTHER:
            return "SCHED_OTHER";
        case SCHED_FIFO:
            return "SCHED_FIFO";
        case SCHED_RR:
            return "SCHED_RR";
        case SCHED_BATCH:
            return "SCHED_BATCH";
        case SCHED_IDLE:
            return "SCHED_IDLE";
        default:
            return "Unknown";
    }
}

int main(int argc, char *argv[]) {
    pid_t pid;

    // If no PID, use current process
    if (argc < 2) {
        pid = getpid();
    } else {
        pid = atoi(argv[1]);
    }

    printf("Getting info for PID: %d\n", pid);

    // Get priority
    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);
    
    if (errno != 0) {
        perror("Error getting priority");
        return 1;
    }
    printf("  Priority: %d\n", priority);

    // Get scheduler
    int sched = sched_getscheduler(pid);
    if (sched == -1) {
        perror("Error getting scheduler");
        return 1;
    }
    printf("  Scheduler: %s\n", get_sched_string(sched));

    return 0;
}