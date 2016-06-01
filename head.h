#ifndef __HEAD_H_
#define __HEAD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>

#define BUFSIZE 1024
#define NAMESIZE 256
#define MAXARGNUM 32
#define MAXCMDNUM 32
#define R_MAX 10

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

int shell_exit(char**);
int shell_history(char**);
int shell_r(char**);
int shell_cd(char**);
int shell_bin(char**);
#define SHELLFUNCS_NUM 4
ShellFunc shellfuncs[]={{"exit",shell_exit},
                      {"history",shell_history},
                      {"r",shell_r},
                      {"cd",shell_cd}};

#endif
