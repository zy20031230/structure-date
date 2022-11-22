#数据结构
## 图的遍历
### 深度优先算法
~~~c
int visited[max];
void DFS(Graph G){
 for(v=0;v<G.vexnum;++v) visited[v]=0;
 for(v=0;v<G.vexnum;++v) if(!visited[v]) dep(G,v);
}
void dep(Graph G,int v){
   visited[v]=TRUE;
   for(w=Firstadjvex[v];w>=0;w=nextadjvex[G,v,w])
   if(!visited[w]) dep(G,w);
}
~~~
以上利用了递归的定义完成深度优先的遍历 ，同时，每一个点是利用int类型，在图结构里进行了保存
### 广度优先遍历
~~~c
int visited[max]
void BFS(Graph G){
initqueue Q;
for(v=0;v<G.vexnum;++v) visited[v]=0;
for(v=0;v<G.vexnum;++v){
enqueue(Q,v);
visited[v]=True;
while(Empty(Q)!=0){
   outqueue(Q,v);
   for(w=Fisitadjvex(v),w>=0;w=nextadjvex(G,v,w)){
   if(!visited[w])
   {
   visited[w]=1;
   print(w);
   enqueue(Q,v)
   }
   }
}
}
~~~
 以上利用队列的含义，由于是先序的遍历算法，每次没有访问的直接visited并打上标记，其次入队列，然后是，在每一次的循环中，队列不空就出队列，并放入，保持了广义优先的要求。
 
## 图的联通性问题
### 深度优先生成树与广度优先生成树
```c
void DFSforest(Graph G,CsTree &T){
//visited 清零；
T=NULL;
for(v=0;v<G.vexnum;++v){
if(!visited[v]){
p=(CsTree) malloc(sizeof(CSNode));
*p={Getvex(G,v),NULL,NULL};
if(!T) T=p;
else{q->nextsibling= p;}
q=p;
DFStree(G,v,q);//主程序完成对森岭里的树的构造，子程序完成对树的构造
}
}
}
DFStree(Graph G, int v,CsTree &T){//把树的根结点传输进来
visited[v]=True; First=True;
for(w=Firstadjvex(v);w>=0;w=Nextadjvex(G,v,w)){
if(!visited[w]){
   p = (CStree)malloc(sizeof(CSNode));
   *p = {getvex(G,w),NULL,NULL};
   if(first) {
     T->lchild=p;
     first=false;
     }
   else{
   q->nextsibling=p}
   q=p;
   DFSTree(G,w,q);
}
}
   
}
```
 利用了两个函数实现这个功能，因为每一次在主函数上会决定出不同的联通图，在同一个函数里面，是在一个联通片中。而树的创建，本质上就是visited函数，类似于先序遍历。
 而且树的储存结构，是在子孩子中，存其兄弟结点，根上存它的兄弟树。
### 关节点和重联通分量
从深度优先算法生成的图后，可以发现对于树上任意一个结点而言，其连接的点，要么是双亲，要么是该点的孩子，要么是它的祖先（确信），因为如果不是后面这两个性质（或者说是，没有在深度在其之前访问），在深度优先算法中，必定会把其当作是他的孩子打印出来）。那么，大致可以归纳出一下的(看成打印过后的性质）关节点性质。
1. 根结点，如果有两颗以上的子树，那么根节点一定关节点。
2. 如果生成树的非叶结点，以及子树的根，以及子树的其他节点，均没有结点可以接上v的祖先的回边，那么，v一定是关节点。（祖先的祖先，一定是我的祖先）

以下定义low[i]=min{visited[v],visited[k],low[w]} 理由如下：
1. low 利用后序遍历得出，同时，low的定义中，存在传递，双亲的low一定比子孙的low小。
2. 如果low[i]比visited[w]大或等（为什么会大？)则顶点w一定是关节点，注：low越小，辈分越高。low记录的是子树的根，和子树的其他结点，最早的辈分中的值。
```c
void findArticul(ALGraph G){
count=1;
visited[0]=1;
for(i=1;i<G.vexnum;i++) visited[i]=0;
p=G.vertices[0].firstarc; 
v=p->artvex;
DFSArticul(G,v);
}
void DFSArticul(ALGraph G, int v0){
visited[v0]=min=count++;//min首先就是对于自己的访问。
for(p=G.vertices[v0].firstarc;p;p=p->nextarc)//这里用的是边，因为每一个点，一定是需要去讨论边的每一个结点的连接点的位置
{  w = p->artvex;
   if(!visited[w]){
   DFSArticul(G,w);
   if(low[w]<min) min=low[w];
   if(low[w]>= visited[v0])
      }
   else {
    if(visited[w]<min)  min=visited[w];
     }
}
low[v0]=min;
}
```
DFSArticul 算法对于一颗树中的点来说，用的是边的形式，对于算法本身，从min的形式来说，low的值是一个后序求出的量，子结点的low一旦比visited【v0】大，一定会暴毙，如果比vo小对其进行更新。