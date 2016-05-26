#ifndef __ERR_H_
#define __ERR_H_

void Err(char errword[])
{
	fprintf(stderr, "%s: %s\n",errword,strerror(errno));
	exit(1);
}

void CmdFail(char *args[],char str[])
{
	int i;
	fputs("shell",stdout);
	for(i=0; args[i]!=NULL; ++i)
		fprintf(stdout," %s",args[i]);
	fprintf(stdout,": %s\n",str);
	fflush(stdout);
}
#endif
