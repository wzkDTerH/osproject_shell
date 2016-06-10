#ifndef __ERR_H_
#define __ERR_H_
/*
	出现错误时的错误信息输出语句。
*/

void Err(char errword[])/* 严重错误，输出信息后结束程序 */
{
	fprintf(stderr, "%s: %s\n",errword,strerror(errno));
	exit(1);
}

void CmdFail(char *args[],char str[])/* 指令运行错误 */
{
	int i;
	fputs("shell",stdout);
	for(i=0; args[i]!=NULL; ++i)
		fprintf(stdout," %s",args[i]);
	fprintf(stdout,": %s\n",str);
	fflush(stdout);
}
void GrmErr(char str[])/* 指令格式错误 */
{
	fprintf(stdout,"shell : %s\n",str);
	fflush(stdout);
}
#endif
