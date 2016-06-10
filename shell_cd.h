#include "head.h"

int shell_cd(char *args[])/* 内置cd命令的实现 */
{
	char path_tmp[BUFSIZE];
	memset(path_tmp,0,sizeof(path_tmp));
	if(args[1]!=NULL)/* 如果cd后带有参数 */
	{
		if(args[1][0]!='/' && args[1][0]!='.')/* 判断是否是绝对路径 */
		{
			strcpy(path_tmp,pathname);
			strcat(path_tmp,"/");
		}
		strcat(path_tmp,args[1]);
	}
	else/* 如果不带参数，cd到用户目录 */
		strcpy(path_tmp,usrpsw->pw_dir);
	if(chdir(path_tmp)==-1)
	/* 尝试cd到此目录。无法cd到此目录的话，输出错误信息 */
		CmdFail(args,"no such file or directory");
	return 0;
}
