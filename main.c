#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define DEBUG 1

#include "head.h"
#include "Err.h"
#include "cmd_pross.h"
#include "shell_cd.h"
#include "shell_exit.h"

#define SHELLCMDS_NUM 2
ShellCmd shellcmds[]={{"exit",shell_exit},
                      {"cd",shell_cd}};

int ShellInit(void)
{
#if DEBUG
	puts(">>>>>> ShellInit");
#endif // DEBUG

	getcwd(pathname,BUFSIZE);

#if DEBUG
	puts(pathname);
	puts("<<<<<< ShellInit");
#endif // DEBUG
	return 0;
}

void PrintCMD()
{
	fprintf(stdout,"%s>",pathname);
	fflush(stdout);
}
int main()
{
	char cmd[BUFSIZE];
	int cmd_len;
	char (*args)[MAXARGNUM];
	int args_num;
	int i;
	if(ShellInit())
	{
		return 1;
	}
	while(1)
	{
		PrintCMD();
		if((cmd_len=GetCmd(cmd))<0) Err("Read cmd Fail");
		if((args_num=DivArgs(cmd,args))==0) continue;
		#if DEBUG
		puts(cmd);
		#endif // DEBUG
		for(i=0; i<SHELLCMDS_NUM; ++i)
		{
			if(strcmp(args[0],shellcmds[i].name)==0)
			{
				shellcmds[i].fun(args);
			}
		}
		if(i==SHELLCMDS_NUM)
		{

		}
	}
	return 0;
}
