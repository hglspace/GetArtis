/*
  队列是一种先进先出FIFO的线性表，它允许在表的一端进行插入，而在另一端删除元素.
  在队列中，允许插入的一端叫做队尾，允许删除的一端称为队头。
  用链表表示的队列称为链队列，一个链队列显然需要两个分别指示队头和队尾的指针(分别称为头指针和尾指针)
  为了操作方便，在第一个顶点结点的前面加上一个头结点。空队列的标志是：头指针和尾指针均指向头结点
 */
#include <stdio.h>
#include <stdlib.h>
#include "GraphHead.h"

/*
   初始化队列
 */
void initQueue(struct LinkQueue * p){
    p->front=p->rear=(struct QNode *)malloc(sizeof(struct QNode));
    if(p->front==NULL){
        printf("构造队列失败");
        exit(1);
    }
    p->front->next=NULL;
}

/*
  销毁队列
 */
void DestoryQueue(struct LinkQueue * p){
    while(p->front!=NULL){
        p->rear=p->front->next;
        free(p->front);
        p->front=p->rear;
    }
}

/*
  元素入队，即添加一个元素
 */
void EnQueue(struct LinkQueue * p,int v){
    struct QNode * child=(struct QNode *)malloc(sizeof(struct QNode));
    if(child==NULL){
        printf("插入失败");
        exit(1);
    }
    child->data=v;
    child->next=NULL;
    p->rear->next=child;
    p->rear=child;
}

/*
  元素出队，即删除一个元素
 */
int DeQueue(struct LinkQueue * p){
    struct QNode * child;
    int e;
    if(p->front==p->rear){//如果是空队列，那么就返回一个错误
        return -1;
    }
    child=p->front->next;
    e=child->data;
    p->front->next=child->next;
    if(p->rear==child){//如果队列中只有一个元素,要修改队尾指针的指向
        p->rear=p->front;
    }
    free(child);
    return e;
}
