/* 队列（queue）的数组实现
 * 队列是一个有序线性表，但队列的插入和删除操作
 * 分别实在线性表的两个不同端点进行的。
 * 类型名称：队列（Queue)
 * 数据对象集：一个有0个或多个元素的有穷线性表
 * 操作集：对于一个长度为正整数 MaxSize 的队列 Q <- Queue,
 *			记队列中任一元素 X <- ElementType，队列的基本
 *			操作主要有：
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Position;
typedef int ElementType;
typedef struct QNode *PtrToQNode;
struct QNode{
	ElementType *Data;		/*存储元素的数组*/
	Position Front, Rear;	/*队列的头、尾指针*/
	int MaxSize;			/*队列的最大容量*/
};
typedef PtrToQNode Queue;


Queue CreateQueue(int MaxSize);
bool IsFull(Queue Q);
bool AddQ(Queue Q, ElementType X);
bool IsEmpty(Queue Q);
ElementType DeleteQ(Queue Q);

int main(int argc, const char* argv[])
{
	int maxsize = 100;
	Queue Q = CreateQueue(maxsize);
	int i;
	printf("\n%s\n", "AddQ");
	for (i=0;i<maxsize+3;i++) {
		printf("%i\t", AddQ(Q, i));
	}
	printf("\n%s\n", "DeletQ");
	for (;i>-1;i--) {
		printf("%i\t", DeleteQ(Q));
	}

	return 0;
}

Queue CreateQueue(int MaxSize)
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (ElementType*)malloc(MaxSize*sizeof(ElementType)); /*!!!这里的Data必须 malloc 之后才可使用;!!!*/
	Q->Front = 0;
	Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}

bool IsFull(Queue Q)
{
	bool answer = false;
	if( IsEmpty(Q) != true) {
		if(((Q->Rear - Q->Front)+1)%(Q->MaxSize) == 0) {
			answer = true;
		}
	}
	return answer;
}

bool AddQ(Queue Q, ElementType X)
{
	bool answer = false;
	if(IsFull(Q) == true) {
		printf("%s\n", "队列已满");
	} else if( Q->Rear < Q->MaxSize-1) {
		Q->Rear += 1;
		Q->Data[Q->Rear] = X;
		answer = true;
	} else if( Q->Rear == Q->MaxSize-1) {
		Q->Rear = 0;
		Q->Data[Q->Rear] = X;
		answer = true;
	}
	return answer;
}

bool IsEmpty(Queue Q)
{
	bool answer = false;
	if( Q->Front == Q->Rear) {
		answer = true;
	}
	return answer;
}

ElementType DeleteQ(Queue Q)
{
	ElementType ERROR=0x80000001;
	ElementType front;
	if (IsEmpty(Q) == true) {
		printf("%s\n", "队列空");
		front = ERROR;
	} else {
		front = Q->Data[++Q->Front];
	}
	return front;
}
