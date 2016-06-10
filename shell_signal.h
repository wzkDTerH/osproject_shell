#ifndef __SHELL_SIGNAL_
#define __SHELL_SIGNAL_

void CtrlHandler(int x)/* 如果出现SIGINT信号，即ctrl+c*/
{
	char cmd[20]="history 10\n";/* 直接尝试执行“history 10”命令 */
	fputc('\n',stdout);
	CmdsRun(cmd);
	return 0;
}

#endif
