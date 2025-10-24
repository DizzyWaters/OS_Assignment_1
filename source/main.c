#include <stdio.h>
#include <string.h>
// for sysinfo block
#include <sys/utsname.h>
// for gatting host block
#include <unistd.h>
// for time block
#include <time.h>
// stat blocl - drives
#include <sys/statvfs.h>
#include <mntent.h> // this one is basicly loop macro to go threw dir of mounted drives
// stat block files
#include <sys/stat.h>
#include <sys/sysmacros.h> // for macro - minor() & major()

// defines

#define D_LONG_WORD 256
#define D_SHORT_WORD 64


//  ***************    functions  ******************************

// function to check linux logical drives
// based on mnt->mnt_type it's const char *input the input should be an array of (const char *a) that is should be made.
int Logic_drives_check(const char *mnt_type, const char *linux_types_array[])
{
    for(int i = 0; linux_types_array[i]; ++i)
    {
        if (strcmp(mnt_type, linux_types_array[i]) == 0)
        return 1;
    }
    return 0;
}


int main(int argc, char **argv)
{
    // my storage aka stored_data.txt
    FILE *myFile = fopen("stored_data.txt", "w");
    if(!myFile)
    {
        perror("Oh crap! can't open file - never happends to me b4!\n");
        printf("This happends on myFile!\n");
        return 1;
    }
    // array of linux logic drives

    const char *D_linuxLogicDrivesList[] = {"ext2", "ext3", "ext4", "xfs", "btrfs", "ntfs", "vfat", "exfat", "iso9660", NULL};

    // futuren sysinfo module -> probobly with options -> all, specific.
    struct utsname sysinfo;
    if(uname(&sysinfo) == -1)
    {
        perror("uname error!");
    }
    printf("Hello this is the System information program:\n");
    printf("System name:    %s\n", sysinfo.sysname);
    printf("Node name:  %s\n", sysinfo.nodename);
    printf("Release:    %s\n", sysinfo.release);
    printf("Version:    %s\n", sysinfo.version);
    printf("Machine:    %s\n", sysinfo.machine);
    printf("************ END OF SYSINFO BLOCK **********\n");
    // time block
    printf("******** This is Time block:\n");
    struct tm* ptr;
    struct tm* ptr2;
    time_t myTime1;
    time_t myTime2;
    myTime1 = time(NULL);
    myTime2 = time(NULL);
    ptr =  gmtime(&myTime1);
    ptr2 = localtime(&myTime2);
    printf("SYSTEM Time is:    %s\n", asctime(ptr));
    printf("LOCAL Time is:    %s\n", asctime(ptr2));
    // System Drive Block

    FILE *myDrives = fopen("/etc/mtab", "r");
    if(!myDrives)
    {
        perror("fopen failed");
        printf("stoped here -> path is crap");
        return 1;
    }

    char device[D_LONG_WORD];
    char mountpoint[D_LONG_WORD];
    char fstype[D_SHORT_WORD];
    char options[D_SHORT_WORD];
    int dump;
    int pass;


    struct mntent *mnt;

    printf("%-30s %-30s %-30s %-30s %-30s\n", "Device", "Mount Point", "Type", "Total MegaB", "Free MegaB"); // names
    printf("***************************************************************************************************************\n");
        while((mnt = getmntent(myDrives)) != NULL)
        {
            if(!Logic_drives_check(mnt->mnt_type,D_linuxLogicDrivesList))
                continue;
            struct statvfs vfs;
                if(statvfs(mnt->mnt_dir, &vfs) == 0){
                    unsigned long totalSpace = (vfs.f_blocks * vfs.f_frsize ) / (1024 * 1024);
                    unsigned long freeSpace = (vfs.f_bfree * vfs.f_frsize ) / (1024 * 1024);
                    printf("%-20s %-50s %-15s %-30lu %30lu\n", mnt->mnt_fsname, mnt->mnt_dir, mnt->mnt_type, totalSpace, freeSpace);
                    fprintf(myFile, "%-20s %-50s %-15s %-30lu %30lu\n" , mnt->mnt_fsname, mnt->mnt_dir, mnt->mnt_type, totalSpace, freeSpace);
                }
        }
        endmntent(myDrives);

    printf("******************** END OF DRIVES BLOCK *************************************************\n");

    // STAT BLOCK
    
    printf("This is a STAT block\n");
    
    char deviceName[D_SHORT_WORD] = "/dev/sda\0";

    struct stat myStat;

    if(stat(deviceName,&myStat) == 0)
    {
        if(S_ISBLK(myStat.st_mode))
        {
            printf("%s %d %d \n", deviceName, major(myStat.st_dev), minor(myStat.st_dev));
        }
    }




    fclose(myFile);

    return 0;
}