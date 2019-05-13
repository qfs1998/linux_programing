#include<stdio.h>
#include<time.h>
#include<stdlib.h>
 
#define ready 1
#define running 2
#define ts 1 /* time slice */
 
struct PCB {
    int pid;    /* 进程ID  */
    int pstate;  /* 进程状态 */
    char *pname; /* 映象名称 */
    int ptime;   /* 剩余运行时间 */
    struct PCB *pnext;  /* 下一个PCB */
};
 
int allTime = 0;//记录总共要运行的时间
int n;//进程数 
int readyQueuePid[10];//用来存ReadyQueue中Pid，加快产生随机数的速度 
 
struct PCB *initReadyQueue() {
	int i;
	printf("请输入进程数量：\n");
	scanf("%d",&n);
	printf("请输入每个进程需要运行的时间\n");
	//创建ReadyQueue头指针
	struct PCB *readyQueueHead = (struct PCB *)malloc(sizeof(struct PCB));
	struct PCB *p = readyQueueHead;
	for(i = 0;i < n;i++) {
		char *tempPname = (char *)malloc(3);
  		tempPname[0] = 'P';//简单点，让我们假设进程只有个位数个
  		tempPname[1] = i+'0';
  		tempPname[2] = '\0';
        struct PCB *q = (struct PCB *)malloc(sizeof(struct PCB));
		q->pid = i;
		q->pstate = ready;
 		q->pname = tempPname;
		scanf("%d",&q->ptime);
		allTime += q->ptime; 
		p->pnext = q;
		p = q;	
	}
	p->pnext = NULL;
	return readyQueueHead;
}
 
//在就绪队列找到要取出的进程的前一个节点的位置 
struct PCB *findReadyQueuePrePosition(struct PCB *head,int pid) {
	struct PCB * p = head;
	while(p->pnext != NULL && p->pnext->pid != pid) {
		p = p->pnext;
	}
	return p;	
}
 
//找到就绪队列最后一个节点的位置 
struct PCB *findReadyQueueEndPosition(struct PCB *head) {
	struct PCB *p = head;
	while(p->pnext) {
		p = p->pnext;
	}
	return p;	
}
 
//输出ReadyQueue的映象名称 
void printReadyQueuePname(struct PCB *head) {
	struct PCB *p = head->pnext;
	if(!p) {
		return;
	}
	printf("Ready:");
	printf("%s",p->pname);
	p = p->pnext;
	while(p) {
		printf("->%s",p->pname);
		p = p->pnext;
	}
	printf("\n");	 
}
 
//每次发生调度的时候，打印信息示例(flag位判断是要free还是ready)
void showInformation(int randPid,int runningQueueFirstNodeId,
	struct PCB *readyQueueHead,int flag) { 
 
	//开始第一次RunningQueue为空的情况单独处理	
	if(runningQueueFirstNodeId == -1) {
		printf("Sched:P%d(Ready -> Running)\n",randPid); 
		printf("Running:P%d\n",randPid); 
		printReadyQueuePname(readyQueueHead);
		printf("\n"); 
		return;
	}
	
	if(flag == 0) {
		printf("Sched:P%d(Running -> Free),P%d(Ready -> Running)\n",
			runningQueueFirstNodeId,randPid); 
		printf("Running:P%d\n",randPid); 
		printReadyQueuePname(readyQueueHead);
		printf("\n");
	} else {
		printf("Sched:P%d(Running -> Ready),P%d(Ready -> Running)\n",
		runningQueueFirstNodeId,randPid); 
		printf("Running:P%d\n",randPid); 
		printReadyQueuePname(readyQueueHead);
		printf("\n");
	}	
}
 
//获取ReadyQueue中现有的Pid，用于产生randPid 
void getReadyQueuePid(struct PCB *head) {
	struct PCB *p = head->pnext;
	//没存Pid的赋值为-1 
	int i;
	for(i = 0;i < 10;i++) { 
		readyQueuePid[i] = -1;
	}
	if(!p) {
		return;
	}
	i = 0;
	while(p) {
		readyQueuePid[i++] = p->pid;
		p = p->pnext;
	}
}
 
//使产生的随机数是不是既不在FreeQueue队列中，也不再RunningQueue队列中 
int getRandPid(struct PCB *head) {
	//防止最后只有一个进程在跑，出现num = 0，导致程序奔溃的情况 
	if(head->pnext == NULL) {
		return -1;
	} 
	getReadyQueuePid(head);
	int randPid,i;
	int num = 0;//用来统计此时ReadyQueue中有几个进程 
	//因为我假设只有个位数个进程，所以取到10 
	for(i = 0;i < 10;i++) {
		if(readyQueuePid[i] == -1) {
			break;
		}				
	}
	num = i;
	srand((unsigned)time(NULL));
	randPid = readyQueuePid[rand()%num];
	return randPid;
}
 
//开始运行这些进程（传入的参数是ReadyQueue的头指针） 
void run(struct PCB *head) {
	int randPid;//记录ReadyQueue中随机产生的进程ID 
	//用来判断在RunningQueue中执行完的进程是应该
	//加入FreeQueue还是ReadyQueue 
	int flag = 1;
	
	//RunningQueue第一个节点的进程ID 
	int runningQueueFirstNodeId = -1;
	
	//FreeQueueHead维持一个指向最后一个节点的指针 
	struct PCB *freeQueueHead = (struct PCB *)malloc(sizeof(struct PCB));
 	struct PCB *freeQueueEndPointer = freeQueueHead;
 	freeQueueEndPointer->pnext = NULL;
 
 	//RunningQueue初始化	
	struct PCB *runningQueueHead = 
	(struct PCB *)malloc(sizeof(struct PCB)); 
	runningQueueHead->pnext = NULL;
		
	//执行进程 
	while(allTime--) {
		//如果该进程执行完毕，加入FreeQueue中 
		if(runningQueueHead->pnext != NULL && 
			runningQueueHead->pnext->ptime == 0) {
			runningQueueFirstNodeId = runningQueueHead->pnext->pid;  
			freeQueueEndPointer->pnext = runningQueueHead->pnext;
			runningQueueHead->pnext = NULL;
			freeQueueEndPointer = freeQueueEndPointer->pnext;
			freeQueueEndPointer->pnext = NULL;
			flag = 0;//加入FreeQueue的标志 
		}
		
		//产生随机编号,确保其既不在FreeQueue队列中，
		//也不再RunningQueue队列中 
		randPid  = getRandPid(head);
		
		//最后只有一个进程一直在占用时间片的情况 
		if(randPid == -1) {
			printf("Sched:P%d(Running -> Free)\n",
			runningQueueHead->pnext->pid);
			printf("Running:P%d\n",runningQueueHead->pnext->pid); 
			printf("\n");
			continue;
		} 
 
	
		//找到ReadyQueue队列中目标节点的前一个节点 
		struct PCB *readyQueuePrePosition = 
			findReadyQueuePrePosition(head,randPid);
		//找到ReadyQueue队列中的最后一个节点 
		struct PCB *readyQueueEndPosition = 
			findReadyQueueEndPosition(head);
 
		//将ReadyQueue的最后一个节点指向RunningQueue的第一个节点，
		//RunningQueue的第一个节点为空其实也没关系
		//如果该进程已经运行完加入了FreeQueue,这里将不会调用，也不会对下面
		//造成影响，其实就是相当于第一次RunningQueue为空的情况 
		if(runningQueueHead->pnext != NULL) {
			//便于后期打印进程调度信息 
			runningQueueFirstNodeId = runningQueueHead->pnext->pid;
		} 
		readyQueueEndPosition->pnext = runningQueueHead->pnext;
		if(runningQueueHead->pnext) {
			//确保ReadyQueue最后一个节点的指针指向空 
			runningQueueHead->pnext->pnext = NULL;
			runningQueueHead->pnext->pstate = ready;
		}				
		runningQueueHead->pnext = readyQueuePrePosition->pnext;
		readyQueuePrePosition->pnext = readyQueuePrePosition->pnext->pnext;
		//确保RunningQueue最后一个节点的指针指向空  
		runningQueueHead->pnext->pnext = NULL;	
		runningQueueHead->pnext->pstate = running;
		runningQueueHead->pnext->ptime -= 1;
		
		//打印出相关信息 
		//因为runningQueueFirstNodeId初始化为-1，如果不为-1，证明已经
		//RunningQueue中已经有东西了，不为空 
		showInformation(randPid,
			runningQueueFirstNodeId,head,flag);
		flag = 1; 
	}
	
	printf("Sched:P%d(Running -> Free)\n",runningQueueHead->pnext->pid);
	printf("\n"); 
}
 
int main() {
	int n,i,tempPid;
	int tempTime;//暂存用户输入的进程运行时间
	int needStop = 1;//判断是否所有进程执行完毕
	struct PCB *readyQueueHead = initReadyQueue();
	//开始运行 
    run(readyQueueHead);
}