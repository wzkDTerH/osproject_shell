#include "head.h"

int shell_cd(char *args[])
{
	char path_tmp[BUFSIZE];
	memset(path_tmp,0,sizeof(path_tmp));
	if(args[1]!=NULL)
	{
		if(args[1][0]!='/' && args[1][0]!='.')
		{
			strcpy(path_tmp,pathname);
			strcat(path_tmp,"/");
		}
		strcat(path_tmp,args[1]);
	}
	else
		strcpy(path_tmp,usrpsw->pw_dir);
	if(chdir(path_tmp)==-1)
		CmdFail(args,"no such file or directory");
	return 0;
}
