#ifndef __CMD_PROSS_
#define __CMD_PROSS_

int GetCmd(char cmd[])
{
	return fgets(cmd,BUFSIZE,stdin);
}
int NOPCheck(char cmd[])
{
	char *p=cmd;
	while(*p==' ') ++p;
	return *p=='\n' || *p=='\0';
}

#define IF_DIV_CHAR(c) ((c)=='|' || (c)==';' || (c)=='&')

int DivCmd(char cmd[],ShellCmd cmds[])
{
	int cmd_num=0,i;
	int cmdlen=strlen(cmd);
	cmds[0].cmd=cmd;
	for(i=cmdlen-1; i>0; --i)
	{
		if(cmd[i]==' ' || cmd[i]=='\0' || cmd[i]=='\n')
			cmd[i]='\0';
		else
			break;
	}
	if(i<0) return 0;
	if(cmd[i]=='|') return 0;
	if(!IF_DIV_CHAR(cmd[i]))
	{
		cmd[++i]=';';
		cmd[++i]='\0';
	}
	for(i=0; cmd[i]!='\0' && cmd[i]!='\n'; ++i)
	{
		if(IF_DIV_CHAR(cmd[i]))
		{
			cmds[cmd_num++].flag=cmd[i];
			cmds[cmd_num].cmd=&cmd[i+1];
			if(IF_DIV_CHAR(cmd[i+1]))
				return 0;
			cmd[i]='\0';
		}
	}
	return cmd_num;
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
	args[args_num]=NULL;
	#if DEBUG
	//printf("%d\n",args_num);
	//puts("<<<<<<DIVARGS");
	#endif // DEBUG
	return args_num;
}
#endif // __CMD_PROSS_
