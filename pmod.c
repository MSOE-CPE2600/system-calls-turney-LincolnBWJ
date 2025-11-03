/*
 * Lincoln Jiang
 * 11/2/2025
 * pmod.c
 */

#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    printf("PID: %d - Reducing priority...\n", getpid());

    // reduce priority by 10
    nice(10);

    struct timespec sleep_time;
    sleep_time.tv_sec = 1;
    sleep_time.tv_nsec = 837272638; // 1,837,272,638 ns total

    printf("Sleeping for 1.837 seconds...\n");
    
    // sleep
    nanosleep(&sleep_time, NULL);

    printf("Goodbye!\n"); 
    return 0;
}