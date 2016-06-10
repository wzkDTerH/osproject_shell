#define DEBUG 1

#include "head.h"
#include "Err.h"
#include "cmd_pross.h"
#include "cmd_run.h"
#include "shell_cd.h"
#include "shell_exit.h"
#include "shell_history.h"
#include "shell_bin.h"
#include "shell_signal.h"

int ShellInit(void)
{
#if DEBUG
#endif // DEBUG
	pthread_mutex_init(&thread_num_mutex,NULL);
	signal(SIGINT,CtrlHandler);/* 截获ctrl+c产生的SIGINT信号 */
	uid=getuid();/* 获取 user id */
	usrpsw=getpwuid(uid);/* 获取路径 */
	chdir(usrpsw->pw_dir);/* 将初始路径移到用户目录下 */
	if (gethostname(computer_name, NAMESIZE) != 0) Err("Cannot get computer name");/* 获取用户名 */
	STDIN_FILENO_ORI=dup(STDIN_FILENO);/* 备份stdin，stdout的FILENO */
	STDOUT_FILENO_ORI=dup(STDOUT_FILENO);
#if DEBUG
#endif // DEBUG
	return 0;
}

void PrintCMD()/* 打印命令提示符 */
{
	uid=getuid();/* 获取 user id */
	usrpsw=getpwuid(uid);/* 获取路径 */
	getcwd(pathname,BUFSIZE);
	fprintf(stdout,"%s@%s:%s$ ",usrpsw->pw_name,computer_name,pathname);
	fflush(stdout);
}
int main()/* 主函数 */
{
	char cmd[BUFSIZE];
	int i,j;
	if(ShellInit()) return 1;
	while(1)
	{
		PrintCMD();/* 打印命令提示符 */
		if(GetCmd(cmd)==NULL) Err("Read cmd Fail");/* 获取用户输入的命令 */
		if(NOPCheck(cmd)) continue;/* 检查是否为空命令 */
		AddRecord(cmd);/* 检查是否为空命令 */
		CmdsRun(cmd);/* 执行命令 */
	}
	return 0;
}
