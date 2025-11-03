/*
 * Lincoln Jiang
 * 11/2/2025
 * finfo.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: ./finfo <filename>\n");
        return 1;
    }

    struct stat file_stat;

    if (lstat(argv[1], &file_stat) == -1) {
        perror("lstat failed");
        return 1;
    }

    printf("--- File Info: %s ---\n", argv[1]);

    // 1. File Type
    printf("File Type: ");
    if (S_ISREG(file_stat.st_mode)) printf("Regular File\n");
    else if (S_ISDIR(file_stat.st_mode)) printf("Directory\n");
    else if (S_ISLNK(file_stat.st_mode)) printf("Symbolic Link\n");
    else printf("Other\n");

    // 2. Permissions
    printf("Permissions:\n");
    printf("  Owner Read:   %s\n", (file_stat.st_mode & S_IRUSR) ? "Yes" : "No");
    printf("  Owner Write:  %s\n", (file_stat.st_mode & S_IWUSR) ? "Yes" : "No");
    printf("  Owner Exec:   %s\n", (file_stat.st_mode & S_IXUSR) ? "Yes" : "No");
    printf("  Group Read:   %s\n", (file_stat.st_mode & S_IRGRP) ? "Yes" : "No");
    printf("  Other Read:   %s\n", (file_stat.st_mode & S_IROTH) ? "Yes" : "No");

    // 3. Owner UID
    printf("Owner UID: %u\n", file_stat.st_uid);

    // 4. File Size
    printf("File Size: %ld bytes\n", file_stat.st_size);

    // 5. Last Modification Time
    printf("Last Modified: %s", ctime(&file_stat.st_mtime));

    return 0;
}