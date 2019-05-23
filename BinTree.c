/* �������� */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NoInfo 0

typedef int ElementTypeBT;
typedef struct TNode *PtrToTree;
typedef PtrToTree BinTree; /*����������*/
struct TNode {			/*����㶨�� */
	ElementTypeBT Data;	/*�������*/
	BinTree Left;		/*ָ��������*/
	BinTree Right;		/*ָ��������*/
};



/* ����(Queue)����ʽ�洢ʵ�� */
typedef BinTree ElementTypeQ;
typedef struct Node * PtrToNode;
struct Node {				/*�����еĽ��*/
	ElementTypeQ Data;
	PtrToNode Next;
};
typedef PtrToNode Position;

typedef struct QNode * PtrToQNode;
struct QNode {
	Position Front, Rear;	/*���е�ͷ��βָ��*/
	int MaxSize;			/*�����������*/
};
typedef PtrToQNode Queue;

Queue CreateQueue(int MaxSize);
bool IsFullQ(Queue Q);
bool AddQ(Queue Q, ElementTypeQ X);
bool IsEmptyQ(Queue Q);
ElementTypeQ DeleteQ(Queue Q);
/*************************************/



/*�������Ĳ���*/
bool IsEmptyBT(BinTree BT);
//void InorderTraversal(BinTree BT);
BinTree CreateBinTree();

bool IsEmptyBT(BinTree BT) {
	if(BT) return true;
	else return false;
}

//void InorderTraversal(BinTree BT) {
//	BinTree T;
//	Stack S=CreateStack(); /*�����ն�ջ S ��Ԫ������lΪBinTree;*/
//	T = BT; /*�Ӹ��ڵ����*/
//	while(T || IsEmptyQ(S)) {
//		while(T) {/*һֱ���󲢽���;���ѹ���ջ */
//			Push(S, T);
//			T = T->Left;
//		}
//		T = Pop(S); /*��㵯����ջ */
//		printf("%d", T->Data);
//		T = T->Right; /*ת�������� */
//	}
//}
//
BinTree CreateBinTree() {
	ElementTypeBT Data;
	BinTree BT, T;
	Queue Q = CreateQueue(100);/*�����ն���*/

	/*������һ����㣬�����ӽڵ�*/
	scanf("%d" , &Data);
	if(Data!=NoInfo) {
		/*������ڵ㵥Ԫ����������ַ���*/
		BT = (BinTree)malloc(sizeof(struct TNode));
		BT->Data = Data;
		BT->Left = BT->Right = NULL;
		AddQ(Q, BT);
	} else {
		/* ����һ�����ݾ��� 0�� ���ؿ��� */
		return NULL;
	}

	while(!IsEmptyQ(Q)) {
		T = DeleteQ(Q); /*�Ӷ�����ȡ��һ����ַ */
		scanf("%d", &Data); /* ���� T ������ */
		printf("%d\n", Data);
		if(Data == NoInfo ) {
			T->Left = NULL;
		} else {
			T->Left = (BinTree)malloc(sizeof(struct TNode));
			T->Left->Data = Data;
			T->Left->Left = T->Left->Right = NULL;
			AddQ(Q,T->Left);
		}

		scanf("%d", &Data); /* ���� T ���Һ��� */
		printf("%d", Data);
		if(Data == NoInfo ) {
			T->Right = NULL;
		} else {
			T->Right = (BinTree)malloc(sizeof(struct TNode));
			T->Right->Data = Data;
			T->Right->Left = T->Right->Right = NULL;
			AddQ(Q,T->Right);
		}
	}/*���� while ѭ�� */

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
		printf("%s\n", "������");
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

		

