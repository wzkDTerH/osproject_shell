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
#include "cmd_run.h"
#include "shell_cd.h"
#include "shell_exit.h"
#include "shell_history.h"
#include "shell_bin.h"
#define SHELLFUNCS_NUM 3
ShellFunc shellfuncs[]={{"exit",shell_exit},
                      {"history",shell_history},
                      {"cd",shell_cd}};


int ShellInit(void)
{
#if DEBUG
#endif // DEBUG
	uid=getuid();
	usrpsw=getpwuid(uid);
	chdir(usrpsw->pw_dir);
	if (gethostname(computer_name, NAMESIZE) != 0) Err("Cannot get computer name");
	STDIN_FILENO_ORI=dup(STDIN_FILENO);
	STDOUT_FILENO_ORI=dup(STDOUT_FILENO);
#if DEBUG
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
	ShellCmd cmds[MAXCMDNUM];
	int args_num,cmd_num;
	int i,j;
	if(ShellInit()) return 1;
	int pipedf[2][2];
	ShellCmdFun fun;
	while(1)
	{
		PrintCMD();
		if(GetCmd(cmd)==NULL) Err("Read cmd Fail");
		if(NOPCheck(cmd)) continue;
		AddRecord(cmd);
		if((cmd_num=DivCmd(cmd,cmds))==0) continue;
		pipe(pipedf[0]);
		for(i=0; i<cmd_num; ++i)
		{
			if((args_num=DivArgs(cmds[i].cmd,args))==0)
			{
				GrmErr("Grammer Error!");
				break;
			}
			#if DEBUG
			#endif // DEBUG
			for(j=0; j<SHELLFUNCS_NUM; ++j)
			{
				if(strcmp(args[0],shellfuncs[j].name)==0)
				{
					fun=shellfuncs[j].fun;
					break;
				}
			}
			if(j==SHELLFUNCS_NUM)
				fun=shell_bin;
			cmd_run(fun,pipedf[i&1],pipedf[!(i&1)],args,cmds[i].flag);
		}
		close(pipedf[i&1][0]);
		close(pipedf[i&1][1]);
	}
	return 0;
}
