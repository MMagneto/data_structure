/* 队列(Queue)的链式存储实现 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct Node * PtrToNode;
struct Node {				/*队列中的结点*/
	ElementType Data;
	PtrToNode Next;
};
typedef PtrToNode Position;

typedef struct QNode * PtrToQNode;
struct QNode {
	Position Front, Rear;	/*队列的头、尾指针*/
	int MaxSize;			/*队列最大容量*/
};
typedef PtrToQNode Queue;

Queue CreateQueue(int MaxSize);
bool IsFull(Queue Q);
bool AddQ(Queue Q, ElementType X);
bool IsEmpty(Queue Q);
ElementType DeleteQ(Queue Q);

int main(int argc, const char* argv[])
{
	Queue Q;
	Q = CreateQueue(100);
	printf("IsEmpty = %i\n", IsEmpty(Q));
	printf("IsFull = %i\n", IsFull(Q));
	printf("\n%s\n","-------------AddQ-----------\n");
	int i;
	for (i=0;i<100;i++) {
		printf("%i\t", AddQ(Q,i));
	}
	printf("\n%s\n","-------------DeleteQ-----------\n");

	for (;i>-1;i--) {
		printf("Empty = %i\n", IsEmpty(Q));
		printf("%i\t", DeleteQ(Q));
	}
	


	return 0;
}

Queue CreateQueue(int MaxSize)
{
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->MaxSize = MaxSize;
	Q->Front = (Position)malloc(sizeof(struct Node));
	Q->Front->Next = NULL;
	Q->Rear = Q->Front;
	return Q;
}

bool IsFull(Queue Q)
{
	Position p = Q->Front;
	int count = 0;
	bool answer = false;
	while(p->Next != NULL) {
		p = p->Next;
		count++;
	}
	if (count >= Q->MaxSize-1) {
		answer = true;
	}
	return answer;
}

bool AddQ(Queue Q, ElementType X)
{
	bool answer;
	if (IsFull(Q) == true ) {
		printf("%s\n", "队列满");
		answer = false;
	} else {
		PtrToNode newNode = (PtrToNode)malloc(sizeof(struct Node));
		newNode->Data = X;
		newNode->Next = NULL;
		Q->Rear->Next = newNode;
		Q->Rear = newNode;
		answer = true;
	}
	return answer;
}
		
bool IsEmpty(Queue Q)
{
	bool answer = false;
	if (Q->Front->Next == NULL ) {
		answer = true;
	}
	
//	if (Q->Rear == Q->Front) {
//
//		answer = true;
//	}
	return answer;
}

ElementType DeleteQ(Queue Q)
{
	ElementType ERROR = 0x80000001;
	ElementType NodeData = ERROR;

	if(IsEmpty(Q)==false) {
		PtrToNode OldNode = Q->Front->Next;
		Q->Front->Next = OldNode->Next;
		NodeData = OldNode->Data;
		free(OldNode);
	}

	return NodeData;
}

		

