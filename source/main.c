#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>


int main(int argc, char **argv)
{
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
    return 0;
}