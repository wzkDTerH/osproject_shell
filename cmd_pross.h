#ifndef __CMD_PROSS_
#define __CMD_PROSS_

int GetCmd(char cmd[])
{
	return read(STDIN_FILENO, cmd, BUFSIZE);
}

int DivArgs(char cmd[],char (*args)[])
{
	char *p=cmd;
	int args_num=0;
	while(*p!='\0' && str[])
	{

	}
}

#endif // __CMD_PROSS_
