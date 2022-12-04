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
int h[511],pos[7],size;
/*---------广义变量定义完成--------------*/
void initGraph(ALGraph_ptr Graph){
    Graph->arcnum=Graph->vexnum=Graph->arcnum=0;
    int i;
    int src,dst,distance;
    for(i=0;i<MAXVEX;i++)
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
    printf("done");
}
void swap(int x,int y){
    int temp;
    temp =h[x];
    h[x]=h[y];
    h[y]=temp;
    temp=pos[h[x]];
    pos[h[x]]=pos[[h[y]]];
    pos[h[y]]=temp;
}
void siftdown(int i){
    int t,flag=0;

}
int main(){
    ALGraph Graph;
    ALGraph_ptr Graph_ptr=&Graph;
    initGraph(Graph_ptr);

}