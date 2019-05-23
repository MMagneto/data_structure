/* 二叉树的 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NoInfo 0

typedef int ElementTypeBT;
typedef struct TNode *PtrToTree;
typedef PtrToTree BinTree; /*二叉树类型*/
struct TNode {			/*树结点定义 */
	ElementTypeBT Data;	/*结点数据*/
	BinTree Left;		/*指向左子树*/
	BinTree Right;		/*指向右子树*/
};



/* 队列(Queue)的链式存储实现 */
typedef BinTree ElementTypeQ;
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
bool IsFullQ(Queue Q);
bool AddQ(Queue Q, ElementTypeQ X);
bool IsEmptyQ(Queue Q);
ElementTypeQ DeleteQ(Queue Q);
/*************************************/



/*二叉树的操作*/
bool IsEmptyBT(BinTree BT);
//void InorderTraversal(BinTree BT);
BinTree CreateBinTree();

bool IsEmptyBT(BinTree BT) {
	if(BT) return true;
	else return false;
}

//void InorderTraversal(BinTree BT) {
//	BinTree T;
//	Stack S=CreateStack(); /*创建空堆栈 S ，元素类型l为BinTree;*/
//	T = BT; /*从根节点出发*/
//	while(T || IsEmptyQ(S)) {
//		while(T) {/*一直向左并将沿途结点压入堆栈 */
//			Push(S, T);
//			T = T->Left;
//		}
//		T = Pop(S); /*结点弹出堆栈 */
//		printf("%d", T->Data);
//		T = T->Right; /*转向右子树 */
//	}
//}
//
BinTree CreateBinTree() {
	ElementTypeBT Data;
	BinTree BT, T;
	Queue Q = CreateQueue(100);/*创建空队列*/

	/*建立第一个结点，即根接节点*/
	scanf("%d" , &Data);
	if(Data!=NoInfo) {
		/*分配根节点单元，并将结点地址入队*/
		BT = (BinTree)malloc(sizeof(struct TNode));
		BT->Data = Data;
		BT->Left = BT->Right = NULL;
		AddQ(Q, BT);
	} else {
		/* 若第一个数据就是 0， 返回空树 */
		return NULL;
	}

	while(!IsEmptyQ(Q)) {
		T = DeleteQ(Q); /*从队列中取出一结点地址 */
		scanf("%d", &Data); /* 读入 T 的左孩子 */
		printf("%d\n", Data);
		if(Data == NoInfo ) {
			T->Left = NULL;
		} else {
			T->Left = (BinTree)malloc(sizeof(struct TNode));
			T->Left->Data = Data;
			T->Left->Left = T->Left->Right = NULL;
			AddQ(Q,T->Left);
		}

		scanf("%d", &Data); /* 读入 T 的右孩子 */
		printf("%d", Data);
		if(Data == NoInfo ) {
			T->Right = NULL;
		} else {
			T->Right = (BinTree)malloc(sizeof(struct TNode));
			T->Right->Data = Data;
			T->Right->Left = T->Right->Right = NULL;
			AddQ(Q,T->Right);
		}
	}/*结束 while 循环 */

		printf("here");

	return BT;
}


int main(int argc, const char* argv[])
{
	BinTree BT = CreateBinTree(); 

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

bool IsFullQ(Queue Q)
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
	if (IsFullQ(Q) == true ) {
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
		
bool IsEmptyQ(Queue Q)
{
	bool answer = false;
	if (Q->Front->Next == NULL ) {
		answer = true;
	}
	return answer;
}

ElementTypeQ DeleteQ(Queue Q)
{
	ElementTypeQ ERROR = NULL;
	ElementTypeQ NodeData = ERROR;

	if(IsEmptyQ(Q)==false) {
		PtrToNode OldNode = Q->Front->Next;
		Q->Front->Next = OldNode->Next;
		NodeData = OldNode->Data;
		free(OldNode);
	}

	return NodeData;
}

		

