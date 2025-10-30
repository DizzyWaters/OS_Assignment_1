#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "sysinfo.h"
#include "drive_block.h"
#include "stat_block.h"
#include "file_system.h"

void show_menu(void) {
    char choice;
    int isRunning = 1;

    while (isRunning) {
        system("clear");
        printf("=========== System Info Menu ===========\n");
        printf("1. Show system information\n");
        printf("2. Show drives information\n");
        printf("3. Show device stat info\n");
        printf("4. File system demo\n");
        printf("0. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");

        choice = getchar();
        getchar(); // consume newline

        switch (choice) {
            case '1':
                print_sysinfo();
                break;
            case '2':
                show_drives();
                break;
            case '3':
                show_stat_block();
                break;
            case '4':
                file_system_run();
                break;
            case '0':
                printf("Exiting...\n");
                isRunning = 0;
                break;
            default:
                printf("Invalid input, try again.\n");
                break;
        }

        if (isRunning) {
            printf("\nPress Enter to continue...");
            getchar();
        }
    }
}
