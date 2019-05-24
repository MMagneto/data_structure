/* 二叉树的遍历 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int NoInfo=0;
int MaxSize=100;

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
void LevelOrderTraversal( BinTree BT);


bool IsEmptyBT(BinTree BT) {
	if(BT) return true;
	else return false;
}

//void InOrderTraversal( BinTree BT )
//{	/*中序遍历二叉树*/
//
//	BinTree T = BT;
//	Stack S = CreateStack( Maxsize );
//	while( T || IsEmpty(s)) {
//		while(T) {	/*一直向左并将沿途结点压入堆栈 */
//			Push(S,T);
//			T = T->Left;
//		}
//		if(!IsEmpty(S)) {
//			T = Pop(S);	/*结点弹出堆栈*/
//			printf("%5d", T->Data);	/*（访问）打印结点*/
//			T = T->Right;	/*转向右子树*/
//		}
//	}
//}
//

/*层序遍历二叉树——队列*/
void LevelOrderTraversal( BinTree BT)
{
	Queue Q;
	BinTree T;
	if(!BT) return;	/*若是空树，直接返回*/
	Q = CreateQueue(MaxSize);	/*创建并初始化队列*/
	AddQ(Q,BT);
	while(!IsEmptyQ(Q)) {
		T = DeleteQ(Q);
		printf("%d\n", T->Data);
		if(T->Left) AddQ(Q, T->Left);
		if(T->Right) AddQ(Q, T->Right);
	}
}


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
		BT->Left = NULL;
		BT->Right = NULL;
		AddQ(Q, BT);
	} else {
		/* 若第一个数据就是 0， 返回空树 */
		return NULL;
	}
	int cnt = 0;

	while(!IsEmptyQ(Q)) {
		T = DeleteQ(Q); /*从队列中取出一结点地址 */
		scanf("%d", &Data); /* 读入 T 的左孩子 */
		if(Data == NoInfo ) {
			T->Left = NULL;
		} else {
			T->Left = (BinTree)malloc(sizeof(struct TNode));
			T->Left->Data = Data;
			T->Left->Left = NULL;
			T->Left->Right = NULL;
			printf("addQ left = %d\n", AddQ(Q,T->Left));
			printf("is empty Q? = %d\n", IsEmptyQ(Q));

		}

		scanf("%d", &Data); /* 读入 T 的右孩子 */
		if(Data == NoInfo ) {
			T->Right = NULL;
		} else {
			T->Right = (BinTree)malloc(sizeof(struct TNode));
			T->Right->Data = Data;
			T->Right->Left = NULL;
			T->Right->Right = NULL;
			printf("addQ right = %d\n", AddQ(Q,T->Right));
			printf("is empty Q? = %d\n", IsEmptyQ(Q));
		}
		cnt++;
	}/*结束 while 循环 */
	printf("loop time=%d\n", cnt);
	return BT;
}


int main(int argc, const char* argv[])
{
	BinTree BT = CreateBinTree(); 
	printf("OUTPUT:\n");
	LevelOrderTraversal(BT);
//	bool answer;
//	Queue Q = CreateQueue(MaxSize);
//	BinTree BT, T;
//	T = (BinTree)malloc(sizeof(struct TNode));
//	T->Data = 1;
//	T->Left = NULL;
//	T->Right = NULL;
//	AddQ(Q, T);
//	BT = DeleteQ(Q);
//	printf("first:%d\n", BT->Data);
//	BT->Left = (BinTree)malloc(sizeof(struct TNode));
//	BT->Left->Data = 2;
//	BT->Left->Left = NULL;
//	BT->Left->Right = NULL;
//	answer = AddQ(Q, T);
//
//	printf("addQ:%d\n", answer);
//	printf("isempty%d\n", IsEmptyQ(Q));
//	printf("second:%d\n", BT->Left->Data);
//
//	BT->Right = (BinTree)malloc(sizeof(struct TNode));
//	BT->Right->Data = 3;
//	BT->Right->Left = NULL;
//	BT->Right->Right = NULL;
//	answer = AddQ(Q, T);
//	printf("addQ:%d\n", answer);
//	printf("isempty%d\n", IsEmptyQ(Q));
//	printf("third:%d\n", BT->Right->Data);
//	printf("%d\n", IsEmptyQ(Q));
//
//	printf("输出:\n");
//	int cnt = 0;
//	while(!IsEmptyQ(Q)) {
//		BT = DeleteQ(Q);
//		printf("%d\n", BT->Data);
//		//printf("%d\n", cnt++);
//	}
//	return 0;
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
		newNode->Data =X;
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
	ElementTypeQ NodeData; 

	if(IsEmptyQ(Q)==false) {

		PtrToNode OldNode;
		if(Q->Front->Next != Q->Rear) { //如果不是只有一个结点
			OldNode = Q->Front->Next;
			Q->Front->Next = OldNode->Next;
			NodeData = OldNode->Data;
		} else { //如果只有一个结点
			OldNode = Q->Front->Next;
			Q->Front->Next = NULL;
			Q->Rear = Q->Front;

			NodeData = OldNode->Data;
		}

		free(OldNode);
	}

	return NodeData;
}
