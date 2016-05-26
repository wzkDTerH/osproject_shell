#ifndef __SHELL_BIN_
#define __SHELL_BIN_

int shell_bin(char *arg[])
{
	char cmd_tmp[BUFSIZE]="/bin/";
	int pid;
	strcat(cmd_tmp,arg[0]);
	if((pid=fork())<0)	Err("Fork Error");
	if(pid==0)
	{
		if(execv(cmd_tmp,arg)==-1)
			CmdFail(arg,"Command not found!");
		exit(0);
	}
	return 0;
}

#endif