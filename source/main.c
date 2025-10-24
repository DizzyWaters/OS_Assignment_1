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


// defines

#define D_LONG_WORD 256
#define D_SHORT_WORD 64

int main(int argc, char **argv)
{
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
            struct statvfs vfs;
                if(statvfs(mnt->mnt_dir, &vfs) == 0){
                    unsigned long totalSpace = (vfs.f_blocks * vfs.f_frsize ) / (1024 * 1024);
                    unsigned long freeSpace = (vfs.f_bfree * vfs.f_frsize ) / (1024 * 1024);
                    printf("%-30s %-30s %-30s %-30lu %30lu\n", mnt->mnt_fsname, mnt->mnt_dir, mnt->mnt_type, totalSpace, freeSpace);
                }
        }
        endmntent(myDrives);








    return 0;
}