#ifndef __SHELL_SIGNAL_
#define __SHELL_SIGNAL_

void CtrlHandler(int x)
{
	char cmd[20]="history 10\n";
	fputc('\n',stdout);
	CmdsRun(cmd);
	return 0;
}

#endif
