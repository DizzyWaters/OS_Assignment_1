#include "sysinfo.h"
#include <stdio.h>
#include <sys/utsname.h>
#include <time.h>

void print_sysinfo(void) {
    struct utsname sysinfo;
    if (uname(&sysinfo) == -1) {
        perror("uname error");
        return;
    }

    printf("\n******** SYSTEM INFORMATION ********\n");
    printf("System name:  %s\n", sysinfo.sysname);
    printf("Node name:    %s\n", sysinfo.nodename);
    printf("Release:      %s\n", sysinfo.release);
    printf("Version:      %s\n", sysinfo.version);
    printf("Machine:      %s\n", sysinfo.machine);

    time_t now = time(NULL);
    printf("\n******** TIME INFORMATION ********\n");
    printf("System time:  %s", asctime(gmtime(&now)));
    printf("Local time:   %s", asctime(localtime(&now)));
}
