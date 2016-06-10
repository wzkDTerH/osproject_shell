#ifndef __SHELL_BIN_
#define __SHELL_BIN_

int shell_bin(char *arg[])/* 用于执行非shell内置的系统命令 */
{
	char cmd_tmp[BUFSIZE]="/bin/";
	int pid,state;
	strcat(cmd_tmp,arg[0]);
	if((pid=fork())<0)	Err("Fork Error");/*另开一个线程*/
	if(pid==0)/*若为子进程，用exec命令载入指令*/
	{
		if(execvp(arg[0],arg)==-1)
			CmdFail(arg,"Command not found!");
		exit(0);
	}
	else/*若为父线程，等待子线程的完成*/
		waitpid(pid,&state,0);
	return 0;
}
#endif
