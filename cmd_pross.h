#ifndef __CMD_PROSS_
#define __CMD_PROSS_

int GetCmd(char cmd[])
{
	return fgets(cmd,BUFSIZE,stdin);
}
int NOPCheck(char cmd[])
{
	char *p=cmd;
	while(p==' ') ++p;
	return *p=='\n' || *p=='\0';
}
int DivArgs(char cmd[],char (**args))
{
	#if DEBUG
	//puts(">>>>>>DIVARGS");
	#endif // DEBUG
	char *p=cmd;
	int args_num=0;
	for(;*p!='\0';++args_num)
	{
		while(*p==' ') ++p;
		if(*p=='\0' || *p=='\n') break;
		args[args_num]=p;
		for( ;*p!=' '; ++p)
		{
			if(*p=='\n') *p='\0';
			if(*p=='\0') break;
		}
		if(*p=='\0') continue;
		*(p++)='\0';
	}
	#if DEBUG
	//printf("%d\n",args_num);
	//puts("<<<<<<DIVARGS");
	#endif // DEBUG
	return args_num;
}

#endif // __CMD_PROSS_
