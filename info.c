/*
 * Lincoln Jiang
 * 10/30/2025
 * info.c
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <time.h>

int main(int argc, char* argv[])
{
    struct timespec ts;
    struct utsname uts;
    char hostname[256];

    // Get time
    clock_gettime(CLOCK_REALTIME, &ts);
    long long nanoseconds = (long long)ts.tv_sec * 1000000000 + (long long)ts.tv_nsec;
    printf("Current time (ns): %lld\n", nanoseconds);

    // Get network name
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Network name: %s\n", hostname);
    }

    // Get OS info
    if (uname(&uts) == 0) {
        if (uts.sysname[0] != '\0') {
            printf("OS Name: %s\n", uts.sysname);
        }
        if (uts.release[0] != '\0') {
            printf("OS Release: %s\n", uts.release);
        }
        if (uts.version[0] != '\0') {
            printf("OS Version: %s\n", uts.version);
        }
        if (uts.machine[0] != '\0') {
            printf("Hardware Type: %s\n", uts.machine);
        }
    }

    // Get CPU count
    printf("Number of CPUs: %d\n", get_nprocs());

    // Get Memory info
    long page_size = sysconf(_SC_PAGE_SIZE);
    long total_pages = sysconf(_SC_PHYS_PAGES);
    long free_pages = sysconf(_SC_AVPHYS_PAGES);

    if (page_size == -1 || total_pages == -1 || free_pages == -1) {
        printf("Error getting memory info from sysconf.\n");
    } else {
        long long total_mem = (long long)total_pages * page_size;
        long long free_mem = (long long)free_pages * page_size;

        printf("Total RAM: %lld bytes\n", total_mem);
        printf("Free RAM: %lld bytes\n", free_mem);
    }

    return 0;
}