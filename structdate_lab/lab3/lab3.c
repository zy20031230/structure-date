#include<stdio.h>
#include<stdlib.h>
#define INFINTY INT_MAX
#define MAXVEX 10000
typedef struct ArcNode{//边节点
    int adjvex;
    struct ArcNode *nextarc;
    int info;//权重
}ArcNode,*ArcNode_ptr;
typedef struct VNode{
    int date;
    ArcNode_ptr firstarc;
}VNode,AdjList[MAXVEX];
typedef struct ALGraph
{
    AdjList vertices;
    int vexnum,arcnum;
    int kind;
}ALGraph,*ALGraph_ptr;
int into[MAXVEX];
/*--------------定义广义变量--------------*/
int h[MAXVEX],size,dis[MAXVEX],postion[MAXVEX];
/*---------广义变量定义完成--------------*/
void initGraph(ALGraph_ptr Graph){
    Graph->arcnum=Graph->vexnum=Graph->arcnum=0;
    int i;
    int src,dst,distance;
    for(i=1;i<MAXVEX;i++)
    {Graph->vertices[i].date=i;
     into[i]=0;
     Graph->vertices[i].firstarc=NULL;
    }//建立点节点。
    FILE *fpread = fopen("data.txt","r");
    if(fpread==NULL) {printf("wrong"); return;}
    //以下建立表节点，
    ArcNode_ptr newarc;
    while(feof(fpread)==0){
        Graph->arcnum++;
        fscanf(fpread,"%d",&src);
        fscanf(fpread,"%d",&dst);
        fscanf(fpread,"%d",&distance);
        if(into[src]==0) {Graph->vexnum++;into[src]=1;}
        if(into[dst]==0) {Graph->vexnum++;into[dst]=1;}
        newarc=(ArcNode_ptr)malloc(sizeof(ArcNode));
        newarc->nextarc=NULL;
        newarc->adjvex=dst;
        newarc->info=distance;
        newarc->nextarc=Graph->vertices[src].firstarc;
        Graph->vertices[src].firstarc = newarc;
    }

}
void swap(int x,int y){
    int temp;
    temp =h[x];
    h[x]=h[y];
    h[y]=temp;
    temp=postion[h[x]];//x代表的是v0，postion代表的是在这个堆里的位置
    postion[h[x]]=postion[h[y]];
    postion[h[y]]=temp;
}
void siftdown(int i){
    int t,flag=0;//为使之符合规律这个堆空间为从1-n的排列的
    while(i*2<=size&&flag==0){
        if(dis[h[i]]>dis[h[i*2]])//dis应该保留的是已经确定的最短的值
        t=i*2;
        else t=i;
        if(i*2+1<=size){
            if(dis[h[t]]>dis[h[i*2+1]])
            t=i*2+1;//比右儿子大，会完成t的更换，而之前还是保留在原来的位置
        }
        //如果t保留在i'的位置，说明交换结束了，否则赋值i=t，继续完成交换
        if(t!=i){
            swap(t,i);
            i=t;}
            else 
            flag=1;
        }
    }
void siftup(int i){//孩子节点比双亲小，开始完成顶点的上浮。
    int flag=0;
    if(i==1) return ;
    while(i!=1&&flag ==0)
    {
        if(dis[h[i]]<dis[h[i/2]])
        {swap(i,i/2);}
        else{ flag=1;}
        i=i/2;
    }
}
int pop(){
    int t;
    t=h[1];
    h[1]=h[size];
    size--; 
    siftdown(1);
    return t;
}
    int pre[MAXVEX];//也就是前一个顶点
void Dijkstra(ALGraph Graph,int vsrc,int vdst){
    int cacu,prevex;
    //dis数组已经完成了创建
    ArcNode_ptr Arc;
    /*---------以下完成初始化-----------*/
    int i,v0;
    dis[vsrc]=0; pre[vsrc]=0;//表示已经终结
    for(i=1;i<=9999;i++)//注意，这里为了符合堆的定义，所有的点的存储均是从1开始进行
    {
       if(i!=vsrc){
       dis[i]=INFINTY;//初始化最长的长度
       pre[i]=-1;//表示最初没有找到前面的节点
       }
    }
    for(Arc=Graph.vertices[vsrc].firstarc;Arc!=NULL;Arc=Arc->nextarc){
        v0=Arc->adjvex;
        dis[v0]=Arc->info;
        pre[v0]=vsrc;
    }//dis[]数组的初始化在这里已经完成了
    size=9999;//maxvex-1最初的数组[0]不会放入其中进行计算
    for(i=1;i<=size;i++){h[i]=i;postion[i]=i;}//在什么位置，就是第几个顶点
    for(i=size;i>=1;i--) siftdown(i);
    pop();
    int count=1;
    while(count!=9999){
        cacu=pop();
        count++;
        for(Arc=Graph.vertices[cacu].firstarc;Arc!=NULL;Arc=Arc->nextarc){
            v0=Arc->adjvex;
            if(dis[v0]>dis[cacu]+Arc->info){
                dis[v0]=dis[cacu]+Arc->info;
                pre[v0]=cacu;
                siftup(postion[v0]);
            }
        }
            
    }
    int k;
    k=vdst;
    while(k!=0){
        printf("%d<-",k);
        k=pre[k];
    }
}
int main(){
    ALGraph Graph;
    ALGraph_ptr Graph_ptr=&Graph;
    initGraph(Graph_ptr);
    Dijkstra(Graph,1,2);
    printf("最短距离是 %d",dis[2]);
    ArcNode_ptr Arc;
}