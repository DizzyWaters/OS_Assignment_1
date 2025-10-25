#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h> // this one for moving dir.
#include <sys/types.h>


#define MAX_COMMANDS_LEN 1024
#define MAX_ARGS 10

void run_cd(char *path)
{
	if(path = NULL)
	{
	fprintf(stderr,"cd: missing argument\n");
	return;
	if (chdir(paht) != 0)	
	{
		perror("cdccdd");
	}
	}
}

