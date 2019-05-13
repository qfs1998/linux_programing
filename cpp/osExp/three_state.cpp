#include <stdio.h>
#include <stdlib.h>
 
typedef struct pcb
{
	int name; // 进程的名称
	char state;// 进程的状态
	int arrivetime; //进程的到达时间
	int runtime;// 进程的执行时间
	int cputime;//cpu占用的时间
	int count;//优先数
	struct pcb *next;
}pcb;
pcb *head = NULL; // 正常对列
pcb *head1 = NULL; // 未到达的对列
int n = 0;// 进程的数量
//创建头指针
void createhead()
{
	pcb *p = (pcb*)malloc(sizeof(pcb));// 创建头指针
	head = p;
	pcb *q = (pcb*)malloc(sizeof(pcb));// 创建头指针
	head1 = q;
}
void sort()// 按照优先数进行排序
{
	pcb* t = head;
    pcb *q,*p,*r;
    int max;
    while(t->next != NULL)
    {
		p = t->next;
		r = t->next;
		max = r->count;
        while(r!= NULL)
        {
			if(r->count > max)
			{
				max = r->count;
                p = r;
			}
            r = r->next;
		}// p指向count最大的那一个数
        q = t;
		//q = the node before the max
		while (q->next != p)
			q = q->next;
		if(t->next != p)
		{
			q->next = p->next;
			p->next = t->next;
			t->next = p;
		}// 插入进行排序按照优先数
        t = t->next;
	}
}
bool create() //创建pcb操作
{
	createhead();
	pcb *p = head;
	pcb *q = head1;
	printf("请输入进程数目：");
	scanf("%d",&n);
	pcb *temp;
    for(int i=1;i<=n;i++ )//尾插法建立就绪队列
    {
		temp = (pcb*)malloc(sizeof(pcb));
        if(!temp) return false;
        printf("请输入进程%d的要求运行时间,进程优先数,到达时间：",i);
		scanf("%d %d %d",&(temp->runtime),&(temp->count),&(temp->arrivetime));
		temp->cputime = 0;
        temp->name=i;
		temp->next = NULL;
        temp->state='W';
		if(temp->arrivetime!=0) // 对到达时间进行判断
		{
			q->next = temp;
			q = temp;
		}
		else
		{
			p->next = temp;
			p = temp;
		}
	}
	sort(); // 排序
	return true;
}
void destory(pcb *rp)// 撤销操作
{
	printf("****************进程%d已完成****************\n",rp->name);
	pcb *q = rp->next;
	head->next = q;
	free(rp);
}
void display(pcb *rp) // 展示当前的信息
{
	printf("进程名字：%d",rp->name);
	printf("\n进程优先级：%d",rp->count);
	printf("\n进程所占时间片：%d",rp->runtime);
	printf("\n进程已运行时间：%d",rp->cputime);
	printf("\n进程当前状态：%c",rp->state);
	printf("\n=====================================\n");
}
void arrivetime()// 对于到达时间-1的操作
{
	pcb *q = head1->next;
	pcb *r,*t;
	while(q!=NULL) // 判断到达时间是否为0 此时是否到达
	{
		q->arrivetime--;
		if(q->arrivetime==0)
		{
			t = head1;
			while(t->next!=q)
				t = t->next;
			t->next = q->next;
			r = head->next;
			q->next = r;
			head->next = q;
		}
		q = q->next;
	}
}
void runpcb(pcb *rp)
{
	rp->cputime++; //修改cpu占用的时间
	arrivetime();
	printf("----------正在运行的进程----------\n"); // 输出正在运行的队列
	display(rp);
	if(rp->cputime==rp->runtime)
	{
		destory(rp);
	}
	else
	{
		rp->count--;
		rp->state = 'W';
	}
	pcb *p = head;
	if(head->next==NULL&&head1->next==NULL) return;
	printf("----------处于就绪对列的进程----------\n"); // 输出就绪的队列
	while(p->next!=NULL)
	{
		display(p->next);
		p = p->next;
	}
	pcb *q = head1;
	while(q->next!=NULL)
	{
		display(q->next);
		q = q->next;
	}
	sort();
}
int main()
{
	create();// 创造进程
	pcb * p;
	while(head->next!=NULL || head1->next!=NULL) // 判断两个对列的进程是否都走完
	{
		if(head->next!=NULL)
		{
			p= head->next;
			p->state='R';
			runpcb(p);
		}
		else
		{
			arrivetime();
		}
	}
	return 0;
}