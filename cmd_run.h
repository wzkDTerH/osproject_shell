#ifndef __CMD_RUN_
#define __COM_RUN_

int cmd_run(ShellCmdFun fun,int pipedf_p[2],int pipedf_n[2],char **args,char flag)
{
	int i;
	pipe(pipedf_n);
	if(flag=='|')
	{
		dup2(pipedf_n[1],STDOUT_FILENO);
	}
	else
	{
		dup2(STDOUT_FILENO_ORI,STDOUT_FILENO);
	}
	if(flag!='&')
	{
		fun(args);
	}
	else
	if(fork()==0)
	{
		int thread_id;
		pthread_mutex_lock(&thread_num_mutex);
		thread_id=++thread_num;
		pthread_mutex_unlock(&thread_num_mutex);
		fprintf(stdout,"\n[%d] in\n",thread_id);
		fflush(stdout);
		fun(args);
		fprintf(stdout,"\n[%d] finished  \n",thread_id);
		pthread_mutex_lock(&thread_num_mutex);
		--thread_num;
		pthread_mutex_unlock(&thread_num_mutex);
		//fflush(stdout);
		exit(0);
	}
	close(pipedf_p[0]);
	close(pipedf_p[1]);
	if(flag=='|')
	{
		close(pipedf_n[1]);
		dup2(pipedf_n[0],STDIN_FILENO);
	}
	else
	{
		dup2(STDIN_FILENO_ORI,STDIN_FILENO);
	}
	return 0;
}
int CmdsRun(char *cmd)
{
	char *args[MAXARGNUM];
	ShellCmd cmds[MAXCMDNUM];
	int args_num,cmd_num;
	int cmd_len,i,j;
	int pipedf[2][2];
	ShellCmdFun fun;
	if((cmd_num=DivCmd(cmd,cmds))==0) return 0;
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

#endif // __CMD_RUN_
