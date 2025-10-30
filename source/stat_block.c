#include "stat_block.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>

#define D_SHORT_WORD 64

void show_stat_block(void) {
    char deviceName[D_SHORT_WORD] = "/dev/sda";
    struct stat myStat;

    printf("\n******** STAT BLOCK ********\n");

    if (stat(deviceName, &myStat) == 0) {
        if (S_ISBLK(myStat.st_mode)) {
            printf("%s -> Major: %d, Minor: %d\n",
                   deviceName, major(myStat.st_dev), minor(myStat.st_dev));
        } else {
            printf("%s is not a block device.\n", deviceName);
        }
    } else {
        perror("stat failed");
    }
}
