#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define OK 1
#define ERROR -1
/* 一些想法的记录 
：1，2 号队列的时间是并行产生的，二号队伍每个人出去的时间，在一号人中，处理完时间之后，加上对应的duration       */
typedef struct{
    int occurtime;//到达时间
    int duration;
    int money;
    int No;
}ElemType,*Elemptr;
typedef struct LQNode{
    ElemType customer;
    struct  LQNode *next;
}LQNode,*QueuePtr;
typedef struct 
{
    QueuePtr head,rail; /* data */
    int len;
}*LQptr,Linkqueue;
typedef struct event{
    int evtype;
    int time;//时间发生的时间，
}event;
typedef struct LNode {
    event event_now;
    struct LNode *next;
}LNode,*Link;
typedef struct{
    Link head,rail;
    int len;
}eventlist,*Linklist;//仿造排队模拟完成该事件
/* 完成了实验中，数据元素的定义  */
LQptr initLQ(){
    LQptr Q;
    Q= (LQptr)malloc(sizeof(Linkqueue));
    Q->head=Q->rail=(QueuePtr)malloc(sizeof(LQNode));//创造一个带有头结点的指针
    Q->head->next=NULL;//置零
    Q->len=0;
    return Q;
}
int EnQueue(LQptr Q,ElemType customer){//进入队列，队列长度加1
    QueuePtr p = (QueuePtr)malloc(sizeof(LQNode));
    p->customer=customer;
    p->next=NULL;//前面置零
    Q->rail->next=p;
    Q->rail=Q->rail->next;
    Q->len++;
    return OK;
}
int DeQueue(LQptr Q,Elemptr customer){//退出队列，队列长度减一。或者其中可能存在部分的问题
    if(Q->head->next==NULL) return ERROR;
    *customer=Q->head->next->customer;//拷贝了元素
    QueuePtr p=Q->head->next;
    if(p==Q->rail){//p是最后一个函数，把rail放回去
        Q->rail=Q->head;
        Q->head->next=NULL;
    }
    else{
        Q->head->next=p->next;
    }
    free(p);
    Q->len--;
    return OK;
}
Linklist InitLink(){
    Linklist L =(Linklist)malloc(sizeof(eventlist));
    L->head=L->rail=(Link)malloc(sizeof(LNode));
    L->len=0;
    L->head->next=NULL;
    return L;
}
int linkinsert(Linklist L,event ev){//一个按照时间排序的时间表，time需要随时增加
    Link insert=(Link)malloc(sizeof(LNode));
    insert->event_now = ev;
    insert->next=NULL;
    Link p = L->head->next;
    if(p==NULL) L->head->next=insert;
    else{
    while(p->next&&p->event_now.time<insert->event_now.time){
         p=p->next;
    }
    insert->next=p->next;
    p->next=insert;
    }
    return OK;
}
/*------ 本次实验所需的全局变量 ------- */
int total;//总金额
int Maxofmoney;
int No;//对客户赋值
LQptr handle,waiting;//这里还是没有指定具体的队列
Linklist ev;//一个时间顺序的表,最终的打印应该是按照队列的排序开始打印，每一次离开队列时，打印一次.
event en_happen;//当前发生的事件
event *en_happen_ptr=&en_happen;//指向其的指针
ElemType cust;
Elemptr cust_ptr=&cust;

/* --------------全局变量定义完成----------------- */
void Openfortheday(){
    handle=initLQ();
    waiting=initLQ();
    ev = InitLink();
    No=1;
    en_happen.time=0;//时间会不停迭代上升
    en_happen.evtype=0;
}
//上述函数存在一个问题是，每一次检查后，会选择事件表中的一个事件出来，可能不是按照时间顺序

