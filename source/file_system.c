#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include "file_system.h"   // include the header

#define MAX_PATH 2048
#define MAX_CMD  256

static void list_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[MAX_PATH];

    dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    printf("\nContents of %s:\n", path);
    printf("----------------------------------\n");

    while ((entry = readdir(dir)) != NULL) {
    if(snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name) >= (int)sizeof(full_path))
    {
	    fprintf(stderr, "Path too long(%s)\n", entry->d_name);
    }
    full_path[sizeof(full_path) - 1] = '\0';

        if (stat(full_path, &file_stat) == 0) {
            if (S_ISDIR(file_stat.st_mode))
                printf("[DIR]  %s\n", entry->d_name);
            else
                printf("       %s\n", entry->d_name);
        }
    }

    printf("----------------------------------\n");
    closedir(dir);
}

void file_system_run(void) {
    char cwd[MAX_PATH];
    char command[MAX_CMD];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return;
    }

    printf("\n=== Simple File Navigator ===\n");
    printf("Commands: ls, cd <folder>, exit\n\n");

    while (1) {
        printf("%s$ ", cwd);
        fflush(stdout);

        if (!fgets(command, sizeof(command), stdin))
            break;

        // Remove newline
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0)
            break;
        else if (strcmp(command, "ls") == 0)
            list_directory(cwd);
        else if (strncmp(command, "cd ", 3) == 0) {
            char *dir = command + 3;
            if (chdir(dir) == 0) {
                getcwd(cwd, sizeof(cwd));
            } else {
                perror("cd");
            }
        }
        else if (strcmp(command, "cd") == 0)
            printf("Usage: cd <directory>\n");
        else
            printf("Unknown command: %s\n", command);
    }

    printf("Exiting File Navigator...\n");
}
