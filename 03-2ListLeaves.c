#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define Null -1

int Number;
/* 队列(Queue)的链式存储实现 */



typedef  int ElementTypeQ;
typedef struct Node * PtrToNode;
struct Node {				/*队列中的结点*/
	ElementTypeQ Data;
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
bool AddQ(Queue Q, ElementTypeQ X);
bool IsEmpty(Queue Q);
ElementTypeQ DeleteQ(Queue Q);

/* 某种特殊树的存储实现 */
typedef struct TreeNode *PtrToTreeNode;
typedef int DataType;
struct TreeNode{
	DataType Data;
	int Left;
	int Right;
};
typedef PtrToTreeNode BinTree;

int BuildTree(BinTree Tree, int Number) {
//	struct TreeNode Tree[Number];

	int Root = Null;
	int i;
	char line[10];
	char left, right;
	int index;
	int check[Number];
	for(i=0;i<Number;i++) check[i] = 0;

	for(i=0;i<Number;i++) {
		fgets(line, 10, stdin);
		left = line[0];
		right = line[2];
	//	printf("left = %c\n", left);
	//	printf("right = %c\n", right);

		if(left != '-') {
			Tree[i].Left = (int)(left - '0');
	//		printf("%d\n", Tree[i].Left);
			check[Tree[i].Left] = 1;
		} else {
			Tree[i].Left = Null;
		}
		if(right != '-') {
			Tree[i].Right = (int)(right - '0');
	//		printf("%d\n", Tree[i].Right);
			check[Tree[i].Right] = 1;
		} else {
			Tree[i].Right = Null;
		}
	}
	for(i = 0; i<Number;i++) {
//		printf("%d: %d\n", i, check[i]);
//		printf("%d %d\n", Tree[i].Left, Tree[i].Right);
		if(!check[i]) {
			Root = i;
			break;
		}
	}

	return Root;
}

void ListLeaves(BinTree Tree, int Root) {
	int root = Root;
	if(root!=-1) {
		int cnt = 0;
		Queue Q = CreateQueue(100);
		ElementTypeQ qNode;
		AddQ(Q,root);
		while(!IsEmpty(Q)) {
			cnt++;
			qNode = DeleteQ(Q);
			if(Tree[qNode].Left==Null && Tree[qNode].Right ==Null) {
				if(cnt<Number) printf("%d ", qNode);
				else printf("%d\n", qNode);
			} else {
				if(Tree[qNode].Left != Null) {
					AddQ(Q, Tree[qNode].Left);
		//			printf("%d入队\n", Tree[qNode].Left);
				}
				if(Tree[qNode].Right != Null) { 
					AddQ(Q, Tree[qNode].Right);
		//			printf("%d入队\n", Tree[qNode].Right);
				}
			}			
		}
	}
		
}

int main(int argc, const char* argv[])
{
//	Queue Q;
//	Q = CreateQueue(100);
//	printf("IsEmpty = %i\n", IsEmpty(Q));
//	printf("IsFull = %i\n", IsFull(Q));
//	printf("\n%s\n","-------------AddQ-----------\n");
//	int i;
//	for (i=0;i<100;i++) {
//		printf("%i\t", AddQ(Q,i));
//	}
//	printf("\n%s\n","-------------DeleteQ-----------\n");
//
//	for (;i>-1;i--) {
//		printf("Empty = %i\n", IsEmpty(Q));
//		printf("%i\t", DeleteQ(Q));
//	}
//	
//
//
//	return 0;
	scanf("%d", &Number);
	scanf("%*[^\n]");
	scanf("%*c"); //清除scanf缓存
	//struct TreeNode Tree[Number]; 
	BinTree Tree = (BinTree)malloc(Number*sizeof(struct TreeNode));
	int root = BuildTree(Tree, Number);
//	printf("root = %d\n",root);
	ListLeaves(Tree, root);
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

bool AddQ(Queue Q, ElementTypeQ X)
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

ElementTypeQ DeleteQ(Queue Q)
{
	ElementTypeQ ERROR = 0x80000001;
	ElementTypeQ NodeData; // = (ElementTypeQ)malloc(sizeof(int));
	NodeData = ERROR;

	if(IsEmpty(Q)==false) {
		PtrToNode OldNode = Q->Front->Next;
		/*如果队列中只有一个结点，需要把 Rear 指回头结点*/
		if( (Q->Front->Next) == Q->Rear) {
			Q->Front->Next = OldNode->Next;
			NodeData = OldNode->Data;
			free(OldNode);
			Q->Rear = Q->Front;
		} else {
			Q->Front->Next = OldNode->Next;
			NodeData = OldNode->Data;
			free(OldNode);
		}
	}

	return NodeData;
}

		

