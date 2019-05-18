/* 二叉树的遍历 */

#include <stdio.h>

void InOrderTraversal( BinTree BT )
{	/*中序遍历二叉树*/

	BinTree T = BT;
	Stack S = CreateStack( Maxsize );
	while( T || IsEmpty(s)) {
		while(T) {	/*一直向左并将沿途结点压入堆栈 */
			Push(S,T);
			T = T->Left;
		}
		if(!IsEmpty(S)) {
			T = Pop(S);	/*结点弹出堆栈*/
			printf("%5d", T->Data);	/*（访问）打印结点*/
			T = T->Right;	/*转向右子树*/
		}
	}
}


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
