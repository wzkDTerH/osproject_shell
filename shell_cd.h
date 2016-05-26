#include "head.h"

int shell_cd(char *args[])
{
	char path_tmp[BUFSIZE];
	memset(path_tmp,0,sizeof(path_tmp));
	if(args[1][0]!='/' && args[1][0]!='.')
	{
		strcpy(path_tmp,pathname);
		strcat(path_tmp,"/");
	}
	strcat(path_tmp,args[1]);
	if(chdir(path_tmp)==-1)
	{
		fprintf(stdout,"shell cd %s: no such file or directory.\n",args[1]);
		fflush(stdout);
	}
	return 0;
}
