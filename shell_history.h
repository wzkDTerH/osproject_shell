#ifndef __SHELL_HISTORY_
#define __SHELL_HISTORY_

typedef struct Record
{
	int no;
	char *cmd;
	struct Record *pre,*next;
}Record;
Record *Record_head=NULL,*tail=NULL;


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
		tail=new_node;
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

int shell_history(char *arg[])
{
	Record *p;
	for(p=tail; p!=NULL; p=p->next)
	{
		fprintf(stdout,"%4d ",p->no);
		fputs(p->cmd,stdout);
	}
	fflush(stdout);
	return 0;
}

#endif // __SHELL_HISTORY_
