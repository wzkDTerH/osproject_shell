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
void BackRecord()
{
	Record *p=Record_head;
	Record_head=Record_head->pre;
	if(Record_head==NULL) Record_tail=NULL;
	free(p);
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
int strPREcmp(char s[],char t[])
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
	Record *p;
	char *cmd;
	Record *run_cmd=NULL;
	BackRecord();
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
		for(p=Record_head; p!=NULL; p=p->pre)
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
	cmd=malloc(run_cmd->cmd);
	strcpy(cmd,run_cmd->cmd);
	fprintf(stdout,"Run command: %s",cmd);
	AddRecord(cmd);
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
	for(p=s; p!=NULL; p=p->next)
	{
		fprintf(stdout,"%4d ",p->no);
		fputs(p->cmd,stdout);
	}
	fflush(stdout);
	return 0;
}

#endif // __SHELL_HISTORY_
