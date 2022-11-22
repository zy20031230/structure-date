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
   for(w=Firstadjvex[v];v;w=nextadjvex[G,v,w])
   if(!visited[w]) dep(G,w);
}
~~~
以上利用了递归的定义完成深度优先的遍历 ，同时，每一个点是利用int类型，在图结构里进行了保存
### 广度优先遍历
