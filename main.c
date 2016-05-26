#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>

#define DEBUG 1

#include "head.h"
#include "Err.h"
#include "cmd_pross.h"
#include "shell_cd.h"
#include "shell_exit.h"
#include "shell_history.h"
#include "shell_bin.h"
#define SHELLCMDS_NUM 3
ShellCmd shellcmds[]={{"exit",shell_exit},
                      {"history",shell_history},
                      {"cd",shell_cd}};


int ShellInit(void)
{
#if DEBUG
	puts(">>>>>> ShellInit");
#endif // DEBUG
	uid=getuid();
	usrpsw=getpwuid(uid);
	chdir(usrpsw->pw_dir);
	if (gethostname(computer_name, NAMESIZE) != 0) Err("Cannot get computer name");
#if DEBUG
	puts("<<<<<< ShellInit");
#endif // DEBUG
	return 0;
}

void PrintCMD()
{
	uid=getuid();
	usrpsw=getpwuid(uid);
	getcwd(pathname,BUFSIZE);
	fprintf(stdout,"%s@%s:%s$ ",usrpsw->pw_name,computer_name,pathname);
	fflush(stdout);
}
int main()
{
	char cmd[BUFSIZE];
	int cmd_len;
	char *args[MAXARGNUM];
	int args_num;
	int i;
	if(ShellInit()) return 1;
	while(1)
	{
		PrintCMD();
		if(GetCmd(cmd)==NULL) Err("Read cmd Fail");
		if(NOPCheck(cmd)) continue;
		AddRecord(cmd);
		if((args_num=DivArgs(cmd,args))==0) continue;
		#if DEBUG
		#endif // DEBUG
		for(i=0; i<SHELLCMDS_NUM; ++i)
		{
			if(strcmp(args[0],shellcmds[i].name)==0)
			{
				shellcmds[i].fun(args);
				break;
			}
		}
		if(i==SHELLCMDS_NUM)
		{
			shell_bin(args);
		}
	}
	return 0;
}
