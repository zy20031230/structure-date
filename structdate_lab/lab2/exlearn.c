

#include<stdio.h>
#include<stdlib.h>
typedef struct {
    int occurtime;
    int Ntype;
}Event,ElemType;
typedef struct Lnode{
    Event happen;
    struct Lnode *next; 
}*Link;
typedef struct {
    Link head,tail;
    int len;
}Eventlist,*Evelistptr; //调用直接使用这个，head作为头指针，tail作为尾指针。
int initlist(Evelistptr ev){
    ev =(Evelistptr)malloc(sizeof(Eventlist));


}

typedef struct {
    int ArrivalTime;
    int Duration;
}QElemType,*QElemptr;
typedef struct Qnode{
    QElemType people;
    struct Qnode *next;
}Qnode,*Queueptr;//代指四个队列
typedef struct 
{
   Queueptr head;
   Queueptr rear;
}LinkQueue,*LQptr;
//以下写一些基本的函数
LQptr InitQueue(){//之前这里是一种错误的做法，传递了一个没有指向的指针，这里给了一个Q具体的指向。
    LQptr Q=(LQptr)malloc(sizeof(LinkQueue));
    Q->head=Q->rear=(Queueptr)malloc(sizeof(Qnode));
    Q->head->next=NULL;
    return Q;//指针，必须要有一个实体的指向，函数，实际上是把一个一个值进行拷贝，而发生在另一个空间的事情
}
int EnQueue(LQptr Q,QElemType people){//队列中直接放入人
    Q->rear->next=(Queueptr)malloc(sizeof(Qnode));
    Q->rear=Q->rear->next;
    Q->rear->next=NULL;
    Q->rear->people.ArrivalTime=people.ArrivalTime;
    Q->rear->people.Duration=people.Duration;
}
int DeQueue(LQptr Q,QElemptr people){//队列也有一个头指针，其中不含有任何的数据
    if(Q->head==Q->rear) return 0;//表示其为空队列，返回0
    Queueptr p=Q->head->next;
    people->ArrivalTime=p->people.ArrivalTime;
    people->Duration=p->people.Duration;//以上是继承
    Q->head->next=p->next;
    if(Q->rear==p) Q->rear=Q->head;
    free(p);
}

Eventlist ev;
Event en;
LQptr q[5];
QElemType customer;
QElemptr custget=&customer;//custget 作为指向customer的指针
int Totaltime,Customernum;
void openforday(){
    Totaltime=0;
    Customernum=0;


}



