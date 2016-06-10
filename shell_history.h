#ifndef __SHELL_HISTORY_
#define __SHELL_HISTORY_

/*
	包含处理历史命令信息的函数。
*/

/* 历史信息以链表的形式储存 */
typedef struct Record/* 历史信息储存结构体 */
{
	int no;/* 编号 */
	char *cmd;/* 命令内容 */
	struct Record *pre,*next;/* 前驱和后驱指针 */
}Record;
Record *Record_head=NULL,*Record_tail=NULL;/* 历史信息链表的头尾指针 */


void AddRecord(char *cmd)/* 添加一条命令cmd到历史链表中 */
{
	Record *new_node;
	new_node=malloc(sizeof(Record));
	new_node->cmd=malloc(strlen(cmd));
	strcpy(new_node->cmd,cmd);
	if(Record_head==NULL)
	{
		new_node->no=1;
		new_node->pre=NULL;
		Record_tail=new_node;
	}
	else
	{
		new_node->no=Record_head->no+1;
		new_node->pre=Record_head;
		Record_head->next=new_node;
	}
	new_node->next=NULL;
	Record_head=new_node;
}

int ResetRecord(char *cmd)/* 将最后一条历史链表的信息置换为新命令cmd */
{
	if(Record_head==NULL) return 0;
	free(Record_head->cmd);
	Record_head->cmd=malloc(strlen(cmd));
	strcpy(Record_head->cmd,cmd);
}
void BackRecord()/* 删除最后一条历史命令 */
{
	Record *p=Record_head;
	Record_head=Record_head->pre;
	if(Record_head==NULL) Record_tail=NULL;
	free(p);
}
int Str2Int(char str[],int *num)/* 将字符串str转换为数字，储存入num中。 异常返回0 */
{
	int i=0,t=0,f=1;
	if(str[0]=='-') f=-1,++i;
	for(;str[i]!='\0' && str[i]!=' ' && str[i]!='\n'; ++i)
	{
		if(str[i]<'0' || str[i]>'9') return 0;
		t=t*10+str[i]-'0';
	}
	*num=t*f;
	return 1;
}
int strPREcmp(char s[],char t[])/* 对字符串s和t进行前缀比较，不同或者t长于s则返回0，成功返回1 */
{
	int i;
	for(i=0; 1; ++i)
	{
		if(t[i]=='\n' || t[i]=='\0') return 1;
		if(t[i]!=s[i]) return 0;
	}
	return 0;
}
int shell_r(char *arg[])
{
	/* 作业要求的r命令的实现。
	执行最近的，与arg[1]所 前缀匹配 的命令 。
	成功则将此命令列表中*/
	Record *p;
	char *cmd;
	Record *run_cmd=NULL;
	BackRecord();/* 回退掉历史中记录的 r 指令 */
	if(Record_head==NULL)
	{
		return 0;
	}
	if(arg[1]==NULL)
	{
		if(Record_head!=NULL)
			run_cmd=Record_head;
	}
	else
	{
		for(p=Record_head; p!=NULL; p=p->pre)/* 寻找对应的命令 */
		{
			if(strPREcmp(p->cmd,arg[1]))
				break;
		}
		run_cmd=p;
	}
	if(run_cmd==NULL)
	{
		CmdFail(arg,"No such cmd!\n");
		BackRecord();
		return 0;
	}
	cmd=malloc(run_cmd->cmd);/* 将新命令加入历史列表中 */
	strcpy(cmd,run_cmd->cmd);
	fprintf(stdout,"Run command: %s",cmd);
	AddRecord(cmd);
	CmdsRun(cmd);/* 执行此命令 */
	free(cmd);
}
int shell_history(char *arg[])
/* 显示指令历史。
若指定十进制数arg[1],则尽量输出最近arg[1]条指令。
不足则输出全部*/
{
	Record *p,*s=Record_tail;/* s为起始输出的命令，默认为第一条 */
	int cnt;
	if(arg[1]!=NULL)/* 若指定arg[1]，则找到初始打印的信息位置 */
	{
		if(Str2Int(arg[1],&cnt)==0)
		{
			CmdFail(arg,"arg Error!");
			return 0;
		}
		else
		if(cnt<0)
		{
			CmdFail(arg,"arg out of range!");
			return 0;
		}
		if(Record_head!=NULL)
			cnt=Record_head->no+1-cnt;
		else
			cnt=-1;
		for(;s!=NULL && s->no<cnt; s=s->next);
	}
	for(p=s; p!=NULL; p=p->next)/* 从s所指向的信息，依次打印下来 */
	{
		fprintf(stdout,"%4d ",p->no);
		fputs(p->cmd,stdout);
	}
	fflush(stdout);
	return 0;
}

#endif // __SHELL_HISTORY_
