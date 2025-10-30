#include "drive_block.h"
#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <mntent.h>

#define D_LONG_WORD 256
#define D_SHORT_WORD 64

static int Logic_drives_check(const char *mnt_type, const char *linux_types_array[]) {
    for (int i = 0; linux_types_array[i]; ++i) {
        if (strcmp(mnt_type, linux_types_array[i]) == 0)
            return 1;
    }
    return 0;
}

void show_drives(void) {
    FILE *myFile = fopen("stored_data.txt", "w");
    if (!myFile) {
        perror("Failed to open stored_data.txt");
        return;
    }

    const char *D_linuxLogicDrivesList[] = {
        "ext2", "ext3", "ext4", "xfs", "btrfs", "ntfs",
        "vfat", "exfat", "iso9660", NULL
    };

    FILE *myDrives = fopen("/etc/mtab", "r");
    if (!myDrives) {
        perror("fopen failed");
        fclose(myFile);
        return;
    }

    struct mntent *mnt;
    struct statvfs vfs;

    printf("\n%-20s %-40s %-15s %-15s %-15s\n", "Device", "Mount Point", "Type", "Total MB", "Free MB");
    printf("-----------------------------------------------------------------------------------------------------\n");

    while ((mnt = getmntent(myDrives)) != NULL) {
        if (!Logic_drives_check(mnt->mnt_type, D_linuxLogicDrivesList))
            continue;

        if (statvfs(mnt->mnt_dir, &vfs) == 0) {
            unsigned long totalSpace = (vfs.f_blocks * vfs.f_frsize) / (1024 * 1024);
            unsigned long freeSpace = (vfs.f_bfree * vfs.f_frsize) / (1024 * 1024);
            printf("%-20s %-40s %-15s %-15lu %-15lu\n",
                   mnt->mnt_fsname, mnt->mnt_dir, mnt->mnt_type, totalSpace, freeSpace);
            fprintf(myFile, "%-20s %-40s %-15s %-15lu %-15lu\n",
                    mnt->mnt_fsname, mnt->mnt_dir, mnt->mnt_type, totalSpace, freeSpace);
        }
    }

    fclose(myFile);
    endmntent(myDrives);
}
