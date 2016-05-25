#ifndef __HEAD_H_
#define __HEAD_H_

#define BUFSIZE 1024
#define MAXARGNUM 32

typedef int (*ShellCmdFun)(char**);
typedef struct ShellCmd
{
	char* name;
     ShellCmdFun fun;
}ShellCmd;


char pathname[BUFSIZE];

#endif
