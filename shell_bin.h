#ifndef __SHELL_BIN_
#define __SHELL_BIN_

int shell_bin(char *arg[])
{
	char cmd_tmp[BUFSIZE]="/bin/";
	strcat(cmd_tmp,arg[0]);
	if(execvp(cmd_tmp,arg)==-1)
		CmdFail(arg,"Command not found!");
	return 0;
}

#endif
