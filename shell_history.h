#ifndef __SHELL_HISTORY_
#define __SHELL_HISTORY_

typedef struct Record
{
	int no;
	char *cmd;
	struct Record *pre,*next;
}Record;
Record *Record_head=NULL,*Record_tail=NULL;


void AddRecord(char *cmd)
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

int ResetRecord(char *cmd)
{
	if(Record_head==NULL) return 0;
	free(Record_head->cmd);
	Record_head->cmd=malloc(strlen(cmd));
	strcpy(Record_head->cmd,cmd);
}
int Str2Int(char str[],int *num)
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

int shell_r(char *arg[])
{
	Record *p;
	char *cmd;
	int run_id;
	if(arg[1]==NULL)
		run_id=1;
	else
	if(Str2Int(arg[1],&run_id)==0)
	{
		CmdFail(arg,"ID Error!");
		return 0;
	}
	else
	if(run_id<1 || run_id>R_MAX || run_id>Record_head->no-1)
	{
		CmdFail(arg,"ID out of range!");
		return 0;
	}
	run_id=Record_head->no-run_id;
	for(p=Record_head; p->no!=run_id; p=p->pre);
	cmd=malloc(p->cmd);
	strcpy(cmd,p->cmd);
	ResetRecord(cmd);
	fprintf(stdout,"Run command: %s",cmd);
	CmdsRun(cmd);
	free(cmd);
}
int shell_history(char *arg[])
{
	Record *p,*s=Record_tail;
	int cnt;
	if(arg[1]!=NULL)
	{
		if(Str2Int(arg[1],&cnt)==0)
		{
			CmdFail(arg,"arg Error!");
			return 0;
		}
		else
		if(cnt<0 || cnt>Record_head->no)
		{
			CmdFail(arg,"arg out of range!");
			return 0;
		}
		cnt=Record_head->no+1-cnt;
		for(; s->no!=cnt; s=s->next);
	}
	for(p=s; p!=NULL; p=p->next)
	{
		fprintf(stdout,"%4d ",p->no);
		fputs(p->cmd,stdout);
	}
	fflush(stdout);
	return 0;
}

#endif // __SHELL_HISTORY_
