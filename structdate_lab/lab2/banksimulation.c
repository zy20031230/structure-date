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
int insertQueue(LQptr Q,ElemType customer){//对于Q做了一次前插。同时，一次可能只能做一次前插。
    QueuePtr p=(QueuePtr)malloc(sizeof(LQNode));
    p->next=NULL;
    p->customer=customer;
    if(Q->head==Q->rail){
        Q->head->next=Q->rail=p;
    }
    else{
        p->next=Q->head->next;
        Q->head->next=p;
    }
    Q->len++;
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
    Q->len=Q->len-1;
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
    insert->next=NULL;
    insert->event_now=ev;
    Link p = L->head->next;
    Link pre=L->head;
    if(p==NULL) {
        L->head->next=insert;
        }
    else{
    while(p&&p->event_now.time<ev.time){
         pre=p;
         p=p->next;
    }
    pre->next=insert;
    insert->next=p;
    }
    L->len++;
    return OK;
}
int delink(Linklist L ,event *ptr){
    if(L->len==0) return ERROR;
    *ptr=L->head->next->event_now;
    Link temp;
    temp=L->head->next;
    L->head->next=temp->next;
    free(temp);
    L->len--;
}
/*------ 本次实验所需的全局变量 ------- */
int total=10000;//总金额
int keep;
int closetime=600;//所有人待的总时间
int totaltime=0;
int No;//对客户赋值
int flag2=-1;
int flag=0;
int latestin=-1;
LQptr handle,waiting;//这里还是没有指定具体的队列
Linklist ev;//一个时间顺序的表,最终的打印应该是按照队列的排序开始打印，每一次离开队列时，打印一次.
event en_happen;//当前发生的事件
event *en_happen_ptr=&en_happen;//指向其的指针
ElemType cust;
Elemptr cust_ptr=&cust;

/* --------------全局变量定义完成----------------- */
void closefortheday(){//从时间的设置上来看，进入的人一定不会是超出时间限制的节点
//现在剩下的一种可能是还在排队，但是人
    Link close;
    QueuePtr people,pre;
    if(flag2==1){//说明没办法去做事件驱动了，也说明了这个人是一个可以进入的人，如果这个人可以存足够多的钱，那么可以驱动
    people=waiting->head->next;
    while (people)
    {
        totaltime+=closetime-people->customer.occurtime;
        pre=people;
        printf("No %d 顾客未进行服务而直接离开了\n",people->customer.No);
        people=people->next;         /* code */
        free(pre);
    }
    waiting->len=0;
    people=handle->head->next;
    while(people)
    {
        totaltime+=closetime-people->customer.occurtime;
        pre=people;
        printf("No %d 顾客未进行服务而直接离开了\n",people->customer.No);
        people=people->next;         /* code */
        free(pre);
    }
    handle->len=0;
    }
    else{
    DeQueue(handle,cust_ptr);//首先去计算这个人的时间    
    while(ev->head){//删去所有的节点
         close=ev->head->next;
         free(ev->head);
         ev->head=close;
    }
    people=waiting->head->next;
    while (people)
    {
        totaltime+=closetime-people->customer.occurtime;
        pre=people;
        printf("No %d 顾客未进行服务而直接离开了\n",people->customer.No);
        people=people->next;         /* code */
        free(pre);
    }
    waiting->len=0;
    people=handle->head->next;
    while(people)
    {
        totaltime+=closetime-people->customer.occurtime;
        pre=people;
        printf("No %d 顾客未进行服务而直接离开了\n",people->customer.No);
        people=people->next;         /* code */
        free(pre);
    }
    handle->len=0;
    totaltime+=en_happen.time-cust.occurtime;//这里表示，这次的插入，就发生在这里
    printf("最后一个人No %d , 在%d离开， 在一号handle 窗口存取 %d ,银行总金额%d\n",cust.No,en_happen.time,cust.money,total);  
   } 
       printf("银行今天熄业了。\n模拟结束。");
}
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
void depart_waiting(){
    /*这个函数，主要操作的是，每次当一个人在handle里面完成了存钱后，必须要执行这个函数，即优先遍历一遍，同时，这个函数，必须有可以持续进行的功能，1.是在触发了其他函数的条见，其次是，自己检查出来了一个函数过后，之后还是需要重复完成执行。
    这个会被丢进时间表中*/
    int i=0;
    QueuePtr Q=waiting->head->next;
    ElemType people;
    Elemptr  peoptr=&people;
    if(waiting->len==0) {printf("夫函数%d___",waiting->len);printf("\n"); return;}//如果waiting序列里面没有任何的数，不需要进行操作，
    else {
        for(i=0;i<waiting->len;i++){
            gethead(waiting,peoptr);
            if((people.money+total)>=0){
                insertQueue(handle,people);//people插入handle
                printf("查找成功No%d  \n",people.No);
                DeQueue(waiting,peoptr);//离开该队列
                flag=1;
                break; 
            }
            else{
                DeQueue(waiting,peoptr);
                EnQueue(waiting,people);
                printf("查找失败%d__\n",waiting->len);
            }
        }
        
    }
    
}
void CustomerArrived(){
    //当即表示有人进入， 需要生成与这个人有关的数据
    event rightnow;
    cust.money=rand()%20000-10000;//表示钱，负数表示
    cust.duration=rand()%20;//持续时间
    cust.occurtime=en_happen.time;//事件当前时间
    cust.No=No;
    if(handle->len==0&&(total+cust.money)<0){
        EnQueue(waiting,cust);//放入二号队列，同时不能将其直接放入时间表中，这个人的during，money
        printf("%d_等待\n",cust.No);
    }
    else{
        EnQueue(handle,cust);//进入一号队列,注意这里的时间还不能确定什么时候可以放入时间表中让他离开
        printf("%d_handle\n",cust.No);
    }//这里直接选择把cust丢进队列里，同时，可以肯定，以下是一个合格的数据，在event等于0的时候，之前没有数据对其进行操控
    if(handle->len==1){
        rightnow.evtype=-1;//这里不能直接完成一次前插，因为时间序列的原因。
        rightnow.time=en_happen.time+cust.duration;
        linkinsert(ev,rightnow);//把这个事件丢进事件列表，等待下一次处理
        total+=cust.money; // 把钱放进这个队列
    }
    printf("No %d 在%d 进入本银行\n",cust.No,en_happen.time);
    //以下产生下一个人的数据进行操作
    No++;
    event next;
    next.evtype=0;
    keep=en_happen.time;
    next.time=en_happen.time+rand()%20;//随机数乱选
    if(next.time<closetime)
    {linkinsert(ev,next); latestin=keep;}
}
void depart_handle(){//这个函数的信息处理全是在队列里有两个或者两个以上人数时发生的操作.
    DeQueue(handle,cust_ptr);//首先去计算这个人的时间
    totaltime+=en_happen.time-cust.occurtime;//这里表示，这次的插入，就发生在这里
    printf("No %d , 在%d离开， 在一号handle 窗口存取 %d ,银行总金额%d\n",cust.No,en_happen.time,cust.money,total);
    if(cust.money>0) depart_waiting();//这里需要注意一下时间
    else if(en_happen.evtype==1) depart_waiting();
    event after;
    //剩下来，需要设置下一个人的离开时间,以及这个人的离开时的方式即其他
    if(handle->len>=1){
        gethead(handle,cust_ptr);
        while(handle->len>=1&&cust.money+total<0){
            DeQueue(handle,cust_ptr);
            EnQueue(waiting,cust);//check()操作，执行于离开操作，里面的人存了足够多的钱，那么在其里面需要设置一些控制的操作。
            gethead(handle,cust_ptr);
        }
        if(handle->len>=1){
            gethead(handle,cust_ptr);
            if((cust.money+total)>=0){
             total = total+cust.money;
             after.time=en_happen.time+cust.duration;
            if(flag==1){
            after.evtype=1;
            flag=0;
        }
            else after.evtype=-1;
            linkinsert(ev,after);
    }
        }
    }
}
int main(){
    Openfortheday();
    while(ev->len){
        delink(ev,en_happen_ptr);
        if(en_happen.time>closetime) closefortheday();
        if(en_happen.evtype==0){ 
            CustomerArrived(); 
             if(ev->len==0){ 
                flag2=1;
               closefortheday();
               }
              }
        else depart_handle();
        printf("\n");
        printf("等待人数%d,\n",waiting->len);
        printf("解决人数%d\n",handle->len);
        printf("%d",totaltime/No);
    }
}





