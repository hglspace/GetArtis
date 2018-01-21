#include <stdio.h>
#include "GraphHead.h"
#include <stdlib.h>

Bool visits[MAX_VERTEX_NUM];//顶点是否访问过的标志
Bool addFlag[MAX_VERTEX_NUM];//顶点是否加入到队列的标志
int visitsed[MAX_VERTEX_NUM];//存放每个顶点访问的次序号
int low[MAX_VERTEX_NUM];//存放每个顶点的low值
enum visitFlag flag=unvisited;
static int count=1;
/*
  无向图的操作：
  1 初始化图
  2 深度优先遍历图
  3 广度优先遍历图
  4 连通图的关节点
  5 最小生成树(单独的一个项目)
  6 求连通分量和生成树
 */
/*
 初始化无向图
 */
struct Graph init(void){
    int i,j,k,m;
    char data1,data2;
    struct Graph g;
    int locateVexMethod(struct Graph g,char c);
    printf("请输入顶点数:");
    scanf("%d",&g.vexnum);
    printf("请输入图的边数:");
    scanf("%d",&g.edgenum);
    for(i=0;i<g.vexnum;i++){
        printf("请输入第%d个顶点:",i+1);
        scanf(" %c",&g.adjmulist[i].info);
        g.adjmulist[i].firstedge=NULL;
        visits[i]=False;
        addFlag[i]=False;
    }
    for(j=0;j<g.edgenum;j++){
        struct EBox * p =(struct EBox *)malloc(EB_LENGTH);
        printf("请输入第%d条边的起点:",j+1);
        scanf(" %c",&data1);
        printf("请输入第%d条边的终点:",j+1);
        scanf(" %c",&data2);
        k=locateVexMethod(g,data1);
        m=locateVexMethod(g,data2);
        p->ivex=k;
        p->jvex=m;
        p->ilink=NULL;
        p->jlink=NULL;
        p->mark=flag;
        p->data=(65+j);
        if(g.adjmulist[k].firstedge==NULL){
            g.adjmulist[k].firstedge=p;
        }else{
            p->ilink=g.adjmulist[k].firstedge;
            g.adjmulist[k].firstedge=p;
        }
        if(g.adjmulist[m].firstedge==NULL){
            g.adjmulist[m].firstedge=p;
        }else{
            p->jlink=g.adjmulist[m].firstedge;
            g.adjmulist[m].firstedge=p;
        }
    }
    return g;
}

/*
 根据顶点信息求顶点的位置
 */
int locateVexMethod(struct Graph g,char c){
    int i;
    for(i=0;c!=g.adjmulist[i].info;i++);
    return i;
}

/*
  深度优先遍历无向图
 */
void TraverGraph(struct Graph g){
    int i;
    void DFS(struct Graph g,int i);
    for(i=0;i<g.vexnum;i++){
        DFS(g,i);
    }
}

/*
  深度优先遍历无向图DFS函数
 */
void DFS(struct Graph g,int i){
    struct EBox * p;
    struct EBox * getNextEdg(struct EBox * p,int i);
    if(visits[i]==True){
        return;
    }
    visits[i]=True;
    printf("%c\t",g.adjmulist[i].info);
    for(p=g.adjmulist[i].firstedge;p!=NULL;p=getNextEdg(p,i)){
        if(p->ivex==i){
            DFS(g,p->jvex);
        }else{
            DFS(g,p->ivex);
        }
    }
}

/*
  广度优先搜索：
  广度优先搜索和深度优先搜索有本质的区别，广度优先搜索是按层次搜索的，不能逮着一个结点一搜到底。
  广度优先还要保证“先被访问的顶点的邻接点”先于"后被访问的顶点的邻接点"被访问.
  所以：从某一个结点开始遍历邻接点遍历到第一个邻接点时，把它存放到一个队列中(队列的特点：先进先出),然后下一个邻接点也放到这个队列中，以此类推，
  这样邻接点存放是有先后顺序的。然后从这个队列中取出一个结点开始遍历，然后把遍历到的邻接点也存放到这个队列中。一直循环，直到这个队列中没有结点了，
  广度优先搜索也结束了。
 */
void TraverbreadthFirst(struct Graph g){
    int i,k;
    struct LinkQueue * pp=(struct LinkQueue *)malloc(sizeof(struct LinkQueue));//队列1
    struct LinkQueue * lp=(struct LinkQueue *)malloc(sizeof(struct LinkQueue));//队列2
    int DeQueue(struct LinkQueue * p);
    void initQueue(struct LinkQueue * p);
    void EnQueue(struct LinkQueue * p,int v);
    void DFSBF(struct Graph g,int i,struct LinkQueue * lp);
    void DestoryQueue(struct LinkQueue * p);
    initQueue(pp);
    initQueue(lp);
    for(i=0;i<g.vexnum;i++){
        if(visits[i]==False){//如果这个结点没有遍历过，那么把这个结点加入到队列1中
            EnQueue(pp,i);
        }
        DFSBF(g, i, lp);//遍历该结点的邻接点,在这个过程中把该结点的邻接点都加入到lp队列中
        while (lp->front!=lp->rear) {//该顶点的邻接点也会加入到队列，接着遍历该顶点的邻接点，一直循环，直到叶子结点
            k=DeQueue(lp);//把lp中的元素按进入的先后顺序加入到pp队列中
            EnQueue(pp, k);
            DFSBF(g, k, lp);
        }
    }
    while (pp->front!=pp->rear) {
        k=DeQueue(pp);
        printf("%c\t",g.adjmulist[k].info);
    }
    DestoryQueue(lp);//销毁队列
    DestoryQueue(pp);
}
/*
  这里为什么要设置两个队列？其实设置一个队列就足够了，在元素加入lp队列时，拿到该元素的info，就可以输出了。
  设置两个队列，我是想拿到的元素都装到另外一个队列中，最后可以集中处理这些元素，反正这些元素的先后顺序已经记录在队列中了
  设置几个队列不重要，重要的是能够按顺序输出这些元素的信息即可。
 */

void DFSBF(struct Graph g,int i,struct LinkQueue * lp){
    void EnQueue(struct LinkQueue * p,int v);
    struct EBox * getNextEdg(struct EBox * p,int i);
    int getAdjVex(struct EBox * p,int v);
    int v;
    struct EBox * p;
    if(visits[i]==True){//如果这个结点已经访问过了，就不再访问了
        return;
    }
    visits[i]=True;
    for(p=g.adjmulist[i].firstedge;p!=NULL;p=getNextEdg(p,i)){//循环求该结点的邻接点
        v=getAdjVex(p,i);
        if(addFlag[v]==False && visits[v]==False){//如果该邻接点没有加入过队列，并且该结点没有访问过，因为该顶点也是其邻接点的邻接点
            /*
              如果该邻接点没有加入过队列，并且该结点没有访问过，因为该顶点也是其邻接点的邻接点，i的addFlag并没有置为True,
              但是i已经加入到队列中了，所以还要加上visits[v]的值为False，其实这种情况也只有i=0,第一个访问的顶点才有这种情况
             */
            EnQueue(lp,v);
            addFlag[v]=True;
        }
    }
}
/*
  根据边和当前顶点位置求依附于该顶点的下一条边
 */
struct EBox * getNextEdg(struct EBox * p,int i){
    if(p==NULL){
        return NULL;
    }
    if(p->ivex==i){
        return p->ilink;
    }else{
        return p->jlink;
    }
}

/*
  求连通图的关节点(本例是无向连通图)
 */
void findArticul(struct Graph g){
    int i,v;
    struct EBox * p=g.adjmulist[0].firstedge;//从a顶点(假设0位置存放的是a顶点)开始寻找
    void DFSArticul(struct Graph g,int v);
    //struct EBox * getNextEdg(struct EBox * p,int i);因为这个函数是在本文件上面定义的，所以可以不声明，假如在其他文件或下面定义的，要声明
    int getAdjVex(struct EBox * p,int v);
    visitsed[0]=1;//a顶点是第一个访问的，所以visitsed[0]的值是1
    for(i=1;i<g.vexnum;i++){//初始化其他顶点的visitsed的值
        visitsed[i]=0;
    }
    v=getAdjVex(p,0);
    DFSArticul(g,v);
    if(count < g.vexnum){//说明从a顶点的邻接点v开始深度遍历，并没有访问到全部顶点，那么a顶点就有两棵以上的子树了
        printf("%c\t",g.adjmulist[0].info);
        p=getNextEdg(p,0);
        while(p!=NULL){//再从a顶点的其他邻接点开始深度遍历
            v=getAdjVex(p,0);
            if(visitsed[v]==0){
                DFSArticul(g,v);
            }
            p=getNextEdg(p,0);
        }
    }
}
/*
  1 若生成树的根有两棵以上的子树，则此根顶点必为关节点。因为深度优先遍历的特点，只要有边，肯定能遍历到，所以不可能存在两棵子树，图中不存在联结不同子树中顶点的边。因此，若删去根结点
  2 若生成树中某个非叶子顶点v，其某棵子树的根和子树中的其他结点均没有指向v的祖先的回边，则v为关节点。
    因为，若删去v，则其子树和图的其他部分被分割开来。
  思路：定义visited[v]为深度优先遍历搜索遍历连通图时访问顶点v的次序号，第一个访问的就是1，第二个访问的就是2，以此类推。
  定义 low[v]=min{visitsed[v],low[w],visitsed[k]}(w是顶点v在深度优先生成树上的孩子结点，k是顶点v在深度优先生成树上由回边联结的祖先结点)
  若对于某个顶点v，存在孩子结点w且low[w]>=visitsed[v],则该顶点v必为关节点。因为当w是v的孩子结点时，low[w]>=visitsed[v],表明w及其子孙
  均无指向v的祖先的回边。
  利用深度优先遍历
 */
/*
   DFS深度遍历函数
 */
void DFSArticul(struct Graph g,int v){
    int min,w;//min代表的是visitsed[v] low[w] visitsed[k]的最小值
    struct EBox * p;
    int getAdjVex(struct EBox * p,int v);
    visitsed[v]=min=++count;
    for(p=g.adjmulist[v].firstedge;p!=NULL;p=getNextEdg(p,v)){
        w=getAdjVex(p,v);//假如叶子结点遍历到这，根据边查找到的邻接点肯定是其祖先结点，if判断肯定为假，因为其祖先结点已经访问过了
        if(visitsed[w]==0){//说明w还没有访问过，是v的孩子结点
            DFSArticul(g,w);
            if(low[w]<min){//遍历过孩子结点后，比较孩子结点的low值和当前的min值
                min=low[w];
            }
            if(low[w]>=visitsed[v]){
                printf("%c\t",g.adjmulist[v].info);
            }
        }else if(visitsed[w]<min){
            /*
             说明w已访问过，是v的祖先结点，通过边能访问到祖先结点，说明有回边联结到祖先结点，祖先结点的visitsed值和
             当前min值
             */
            min=visitsed[w];
        }
    }
    /*
      有定义可知，visitsed[v]值即为v在深度优先生成树的前序序列中的序号，正符合深度优先遍历图的特点
      而low[v]的值是v在后续遍历优先生成的值，当前顶点的low值是取3个数的最小值，
      前面的顶点要依赖其子树的low值来判断是否是关节点，所以正好可以在遍历回退的时候赋值
     */
    low[v]=min;
}

/*
  根据边求v顶点的邻接点
 */
int getAdjVex(struct EBox * p,int v){
    if(p->ivex==v){
        return p->jvex;
    }else{
        return p->ivex;
    }
}

/*
  深度优先搜索生成森林（非连通图深度遍历后会成一个森林，要以孩子兄弟存储结构存储这个森林，成为一个树）
  一个连通分量深度遍历完后是一个树，其实就是在遍历的过程中，把这些树以孩子兄弟存储结构存储起来
 */
void DFSForest(struct Graph g,struct CSNode * T){
    int i;
    Bool first=True;
    void DFSTree(struct Graph g,int v,struct CSNode * p);
    for(i=0;i<g.vexnum;i++){
        struct CSNode * p;
        struct CSNode * q;
        struct CSNode * tmp;
        if(visits[i]==False){//这个顶点没有访问过，这个标志是图初始化的时候生成的，如果其他方法用到这个标志的话，会出错
            visits[i]=True;
            if(first){//说明这个顶点是第一个访问的，那么它就是这个森林的根结点
                T->locate=i;
                T->info=g.adjmulist[i].info;
                T->firstchild=NULL;
                T->nextsibling=NULL;
                first=False;
                DFSTree(g, i, T);//深度遍历这个结点
            }else{//说明这个顶点不是第一个访问的，是其他连通分量的树的根结点，那么它就是整个树的右孩子结点，是根据点的兄弟结点
                p=(struct CSNode *)malloc(sizeof(struct CSNode));
                p->locate=i;
                p->firstchild=NULL;
                p->nextsibling=NULL;
                p->info=g.adjmulist[i].info;
                q=T->nextsibling;
                if(q==NULL){//如果它是整个树的根结点的第一个兄弟结点，直接添加到右孩子结点
                    T->nextsibling=p;
                }else{//它是整个树的根结点的其他兄弟结点，要找到其他兄弟结点的右孩子结点，把它添加到那
                    tmp=T->nextsibling;
                    q=T->nextsibling->nextsibling;
                    for(;q!=NULL;q=q->nextsibling,tmp=tmp->nextsibling);
                    tmp->nextsibling=p;
                }
                DFSTree(g, i, p);//深度遍历这个结点
            }
        }
    }
}

/*
  深度遍历该连通分量，其实就是遍历这个连通分量的树,根据孩子兄弟结点的特点进行存储
 */
void DFSTree(struct Graph g,int i,struct CSNode * pp){
    struct EBox * p;
    int v;
    Bool first=True;
    struct EBox * getNextEdg(struct EBox * p,int i);
    int getAdjVex(struct EBox * p,int v);
    for(p=g.adjmulist[i].firstedge;p!=NULL;p=getNextEdg(p, i)){
        struct CSNode * child;
        struct CSNode * tmp1;
        struct CSNode * tmp2;
        v=getAdjVex(p, i);
        if(visits[v]==False){//这个结点没有访问过
            child=(struct CSNode *)malloc(sizeof(struct CSNode));
            visits[v]=True;
            child->firstchild=NULL;
            child->info=g.adjmulist[v].info;
            child->locate=v;
            child->nextsibling=NULL;
            if(first){//如果是i结点的第一个邻接点，那么就是i结点的左孩子
                pp->firstchild=child;
                first=False;
            }else{//是i结点的其他邻接点，要把它放到左孩子的右孩子位置，找到右孩子空的地方放进去
                tmp1=pp->firstchild;
                tmp2=pp->firstchild->nextsibling;
                for(;tmp2!=NULL;tmp1=tmp1->nextsibling,tmp2=tmp2->nextsibling);
                tmp1->nextsibling=child;
            }
            DFSTree(g, v, child);
        }
    }
}

/*
  先序遍历二叉树
 */
void TraverTree(struct CSNode * T){
    if(T!=NULL){
        printf("%c\t",T->info);
        TraverTree(T->firstchild);
        TraverTree(T->nextsibling);
    }
    return;
}
