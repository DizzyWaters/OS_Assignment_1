#include <stdio.h>
// for sysinfo block
#include <sys/utsname.h>
// for gatting host block
#include <unistd.h>
// for time block
#include <time.h>
// stat blocl - drives
#include <sys/statvfs.h>


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



    return 0;
}