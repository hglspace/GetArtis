#define MAX_VERTEX_NUM 20
#define False 0
#define True 1
#define EB_LENGTH sizeof(struct EBox)
enum visitFlag {unvisited,visited};
typedef int Bool;

/*
   多重链表结构存储无向图
 */
struct EBox{//边的结构体
    char data;//边的信息
    int mark;//边的访问标志
    int ivex;//该边依附的顶点
    int jvex;//该边依附的另一顶点
    struct EBox * ilink;//指向依附该顶点的下一条边
    struct EBox * jlink;//指向依附该顶点的下一条边
};

struct VexBox{//顶点的结构体
    char info;//该顶点的信息
    struct EBox * firstedge;//指向依附于该顶点的第一条边
};

struct Graph{//图的结构体
    struct VexBox adjmulist[MAX_VERTEX_NUM];//以数组存储顶点
    int vexnum;//当前顶点的数量
    int edgenum;//当前边的数量
};

/*
  队列
 */
struct QNode{//元素结点结构体
    int data;//结点的信息
    struct QNode * next;//指向下一个结点
};

struct LinkQueue{//队列结构体
    struct QNode * front;//队头指针
    struct QNode * rear;//队尾指针
};

/*
  以孩子兄弟链表结构存储树
 */
struct CSNode{
    int locate;//结点位置
    char info;//结点信息
    struct CSNode * firstchild;//指向该结点的第一个孩子结点
    struct CSNode * nextsibling;//指向该结点的第一个兄弟结点
};
