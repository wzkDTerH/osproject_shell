#ifndef __HEAD_H_
#define __HEAD_H_
/*
	主头文件
	包含所有所需的系统库
	定义一些数据结构，全局变量等
*/
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
#include <pthread.h>
#include <signal.h>
//#include "lock.h
#define BUFSIZE 1024
#define NAMESIZE 256
#define MAXARGNUM 32
#define MAXCMDNUM 32
#define R_MAX 10

typedef int (*ShellCmdFun)(char**);/* 统一化的命令函数类型 */

typedef struct ShellFunc/* 统一化的命令类型 */
{
	char* name;/* 命令名 */
	ShellCmdFun fun;/* 对应的函数指针 */
}ShellFunc;

typedef struct ShellCmd/* 统一化的指令类型 */
{
	char *cmd;/* 指令内容 */
	char flag;/* 运行方式 */
}ShellCmd;

char pathname[BUFSIZE];/* 路径名 */
char computer_name[NAMESIZE];/* 用户名 */
struct passwd *usrpsw;/* 用户目录路径名 */
int uid;/* user ID */
int thread_num=0;/* 线程数量 */
pthread_mutex_t thread_num_mutex;/* 线程锁 */
int STDIN_FILENO_ORI;/* 备份的STDIN的FILENO */
int STDOUT_FILENO_ORI;/* 备份的STDOUT的FILENO */

/* 各内置命令 */
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
