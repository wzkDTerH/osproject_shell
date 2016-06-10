#ifndef __CMD_RUN_
#define __CMD_RUN_

/*
	命令运行相关函数
 */

int cmd_run(ShellCmdFun fun,int pipedf_p[2],int pipedf_n[2],char **args,char flag)
/* 单条命令执行函数：
fun为所应调用函数； pipedf_p为其输入管道； pipedf_n为其输出管道； args为参数列表； flag为运行模式 */
{
	int i;
	pipe(pipedf_n);/* 申请输出管道 */
	if(flag=='|')/* 如果与后条命令间有管道 */
	{/* 将输出重定向到管道 */
		dup2(pipedf_n[1],STDOUT_FILENO);
	}
	else
	{/* 否则将输出重定向到标准输出 */
		dup2(STDOUT_FILENO_ORI,STDOUT_FILENO);
	}
	if(flag!='&')
	{/* 如果不是后台执行，直接执行命令 */
		fun(args);
	}
	else
	if(fork()==0)
	{/* 若是后台执行，申请新的线程 */
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
	close(pipedf_p[0]);/* 关闭输入管道 */
	close(pipedf_p[1]);
	if(flag=='|')/* 如果与后条命令间有管道 */
	{
		close(pipedf_n[1]);/* 关闭管道的写入端 */
		dup2(pipedf_n[0],STDIN_FILENO);/* 将后条命令的输入重定向为管道的读出端 */
	}
	else
	{/* 否则，将后条命令的读入定向回标准读入 */
		dup2(STDIN_FILENO_ORI,STDIN_FILENO);
	}
	return 0;
}
int CmdsRun(char *cmd)/* 执行用户输入的命令cmd */
{
	char *args[MAXARGNUM];
	ShellCmd cmds[MAXCMDNUM];
	int args_num,cmd_num;
	int cmd_len,i,j;
	int pipedf[2][2];/* 节约内存，循环使用两个管道 */
	ShellCmdFun fun;
	if((cmd_num=DivCmd(cmd,cmds))==0) return 0;/* 将用户输入的命令分割成各自独立的单条命令 */
	pipe(pipedf[0]);
	for(i=0; i<cmd_num; ++i)
	{
		if((args_num=DivArgs(cmds[i].cmd,args))==0)/* 将单条命令分割成各个独立参数 */
		{
			GrmErr("Grammer Error!");
			break;
		}
#if DEBUG
#endif // DEBUG
		for(j=0; j<SHELLFUNCS_NUM; ++j)/* 枚举查找需要调用函数 */
		{
			if(strcmp(args[0],shellfuncs[j].name)==0)
			{
				fun=shellfuncs[j].fun;
				break;
			}
		}
		if(j==SHELLFUNCS_NUM)
			fun=shell_bin;
		cmd_run(fun,pipedf[i&1],pipedf[!(i&1)],args,cmds[i].flag);/* 执行单条命令 */
	}
	close(pipedf[i&1][0]);
	close(pipedf[i&1][1]);

}

#endif // __CMD_RUN_
