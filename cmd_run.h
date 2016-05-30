#ifndef __CMD_RUN_
#define __COM_RUN_

int cmd_run(ShellCmdFun fun,int pipedf_p[2],int pipedf_n[2],char **args,char flag)
{
	pipe(pipedf_n);
	if(flag=='|')
	{
		dup2(pipedf_n[1],STDOUT_FILENO);
	}
	else
	{
		dup2(STDOUT_FILENO_ORI,STDOUT_FILENO);
	}
	fun(args);
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
#endif // __CMD_RUN_
