#ifndef __HEAD_H_
#define __HEAD_H_

#define BUFSIZE 1024
#define NAMESIZE 256
#define MAXARGNUM 32
#define MAXCMDNUM 32
typedef int (*ShellCmdFun)(char**);
typedef struct ShellFunc
{
	char* name;
	ShellCmdFun fun;
}ShellFunc;

typedef struct ShellCmd
{
	char *cmd;
	char flag;
}ShellCmd;

char pathname[BUFSIZE];
char computer_name[NAMESIZE];
struct passwd *usrpsw;
int uid;
int thread_num=0;
int STDIN_FILENO_ORI;
int STDOUT_FILENO_ORI;
#endif
