#ifndef __SHELL_BIN_
#define __SHELL_BIN_

int shell_bin(char *arg[])
{
	char cmd_tmp[BUFSIZE]="/bin/";
	int pid,state;
	strcat(cmd_tmp,arg[0]);
	if((pid=fork())<0)	Err("Fork Error");
	if(pid==0)
	{
		if(execvp(arg[0],arg)==-1)
			CmdFail(arg,"Command not found!");
		exit(0);
	}
     else
		waitpid(pid,&state,0);
	return 0;
}

#endif
