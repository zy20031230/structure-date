#include<stdio.h>
#include<stdlib.h>
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
LQptr InitQueue(){//之前这里是一种错误的做法，传递了一个没有指向的指针，这里给了一个Q具体的指向。
    LQptr Q=(LQptr)malloc(sizeof(LinkQueue));
    Q->head=Q->rear=(Queueptr)malloc(sizeof(Qnode));
    Q->head->people.ArrivalTime=1;
    return Q;
}
int main(){
    LQptr Q[4];
    Q[1]=InitQueue();
    printf("%d",Q[1]->head->people.ArrivalTime);
}