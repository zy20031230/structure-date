#include<stdio.h>
#include<stdlib.h>
#define INFINTY __INT_MAX
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
void initGraph(ALGraph_ptr Graph){
    ArcNode_ptr newarc;
    newarc=(ArcNode_ptr)malloc(sizeof(ArcNode));
    Graph->vertices[0].firstarc=(ArcNode_ptr)malloc(sizeof(ArcNode));
    Graph->vertices[0].firstarc->info=1;
    

}
int main(){
    ALGraph G;
    ALGraph_ptr G_ptr=&G;
    initGraph(G_ptr);
    if(G.vertices[0].firstarc->info==1) printf("true");
}