#define DEBUG 1

#include "head.h"
#include "Err.h"
#include "cmd_pross.h"
#include "cmd_run.h"
#include "shell_cd.h"
#include "shell_exit.h"
#include "shell_history.h"
#include "shell_bin.h"
#include "shell_signal.h"

int ShellInit(void)
{
#if DEBUG
#endif // DEBUG
	pthread_mutex_init(&thread_num_mutex,NULL);
	signal(SIGINT,CtrlHandler);
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
	int i,j;
	if(ShellInit()) return 1;
	while(1)
	{
		PrintCMD();
		if(GetCmd(cmd)==NULL) Err("Read cmd Fail");
		if(NOPCheck(cmd)) continue;
		AddRecord(cmd);
		CmdsRun(cmd);
	}
	return 0;
}
