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
int gethead(LQptr Q,Elemptr customer){
    if(Q->len==0) return ERROR;
    else{
        *customer = Q->head->next->customer;
        return OK;
    }
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
int totaltime;//所有人待的总时间
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
    linkinsert(ev,en_happen);//第一个时间发生放入时间表中，同时存在的问题是，在二号队列中的事件是不可预知的
}
//上述函数存在一个问题是，每一次检查后，会选择事件表中的一个事件出来，可能不是按照时间顺序
//钱的交易在什么时间完成，是一个比较重要的问题，
void CustomerArrived(){
    //当即表示有人进入， 需要生成与这个人有关的数据
    cust.money=rand()%500-1000;//表示钱，负数表示
    cust.duration=rand()%20;//持续时间
    cust.occurtime=en_happen.time;//事件当前时间
    cust.No=No;
    if(handle->len==0&&(total+cust.money)<0){
        EnQueue(waiting,cust);//放入二号队列，同时不能将其直接放入时间表中，这个人的during，money
    }
    else{
        EnQueue(handle,cust);//进入一号队列,注意这里的时间还不能确定什么时候可以放入时间表中让他离开
    }//这里直接选择把cust丢进队列里，同时，可以肯定，以下是一个合格的数据，在event等于0的时候，之前没有数据对其进行操控
    if(handle->len==1){
        event rightnow;
        if(cust.money>0){
            //在这里执行，对二队列进行操作
        }
        rightnow.evtype=-1;
        rightnow.time=en_happen.time+cust.duration;
        linkinsert(ev,rightnow);//把这个事件丢进事件列表，等待下一次处理
        total+=cust.money; // 把钱放进这个队列
    }
    //以下产生下一个人的数据进行操作
    No++;
    event next;
    next.evtype=0;
    next.time=en_happen.time+rand()%20;//随机数乱选
    linkinsert(ev,next);
}


void depart_handle(){//这个函数的信息处理全是在队列里有两个或者两个以上人数时发生的操作.
    DeQueue(handle,cust_ptr);//首先去计算这个人的时间
    totaltime+=en_happen.time-cust.occurtime;
    printf("No %d , 在一号handle 窗口存取 %d",cust.No,cust.money);
    event after;
    //剩下来，需要设置下一个人的离开时间,以及这个人的离开时的方式即其他
    if(handle->len>=1){//表示这个队列里还有人的话 执行以下操作.
    gethead(handle,cust_ptr);
    if(cust.money>=0){
        total = total+cust.money;//钱的增加
        after.time=en_happen.time+cust.duration;//en的happen 的happen_time一定要正确的设置
        after.evtype=-2;
        linkinsert(ev,after);//

        /*-----------------------上面少了一个checkwaiting的函数的定义，还有去声明---------------------------------*/
    }
    else if(cust.money<0&&(cust.money+total)>=0){
        total = total+cust.money;
        after.time=en_happen.time+cust.duration;
        after.evtype=-1;//
        linkinsert(ev,after);
    }
    else if((cust.money+total)<0){
        DeQueue(handle,cust_ptr);
        EnQueue(waiting,cust);//check()操作，执行于离开操作，里面的人存了足够多的钱，那么在其里面需要设置一些控制的操作。
    }
    }
}
int main(){
    return 0;
}





