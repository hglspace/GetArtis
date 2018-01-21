
#include <stdio.h>
#include <stdlib.h>
#include "GraphHead.h"
int main(int argc, const char * argv[]) {
    struct Graph init(void);//初始化图
    void TraverGraph(struct Graph g);//深度优先遍历
    void findArticul(struct Graph g);//求图的关节点
    void TraverbreadthFirst(struct Graph g);//广度优先遍历
    void DFSForest(struct Graph g,struct CSNode * T);//深度遍历生成森林
    void TraverTree(struct CSNode * T);//先序遍历二叉树
    struct Graph g=init();
    
//    printf("深度遍历的结果是:");
//    TraverGraph(g);
//    printf("\n");
//    printf("关节点是:");
//    findArticul(g);
//    printf("\n");
    
//    printf("广度优先遍历的结果是:");
//    TraverbreadthFirst(g);
//    printf("\n");
    
    struct CSNode * T=(struct CSNode *)malloc(sizeof(struct CSNode));
    DFSForest(g,T);
    printf("生成的森林是:\n");
    TraverTree(T);
    printf("\n");
    return 0;
}
