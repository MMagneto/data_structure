/* 堆栈的数组实现方法
 * 堆栈：后入先出( Last In First Out, FIFO )表
 * 数据对象集：一个有0个或多个元素的无穷线性表
 * 操作集：对于一个具体的长度为正整数 MaxSize 的堆栈 S <- Stack，
 *			记堆栈中的任一元素 X <- ElementType，堆栈额基本操作主要
 *			有（见下文）
 * 参考文献：数据结构（第2版） 主编 陈越 编著 何钦铭等
 * 作者 Lin Liu
 * Date April 28, 2019
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int Position;
typedef int ElementType;
typedef struct SNode * PtrToSNode;
struct SNode {
	ElementType *Data; /*存储元素的数组*/
	Position Top;		/*栈顶指针*/
	int MaxSize;		/*堆栈最大容量*/
};
typedef PtrToSNode Stack;

Stack CreateStack(int Maxsize);
bool IsFull(Stack S);
bool Push(Stack S, ElementType X);
bool IsEmpty(Stack S);
ElementType Pop(Stack S);

int main(int agrc, const char* argv[])
{
	int i;
	bool answer;
	Stack S = CreateStack(100);
	printf("\n%s\n", "PUSH");
	for (i=0;i <100; i++) {
		printf("%i\t", Push(S, i));
	}
	printf("\n%s\n", "POP");
	for (;i>=0;i--) {
		printf("%i\t", Pop(S));
	}

	return 0;
}

/* 生成空堆栈
 * 其最大长度位 MaxSize
 */
Stack CreateStack(int MaxSize)
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = (ElementType*)malloc(MaxSize*sizeof(ElementType));
	S->Top = -1;
	S->MaxSize = MaxSize;
	return S;
}

/* 判断堆栈是否已满
 * 若 S 中元素的个数等于 MaxSize 时，返回 true, 
 * 否则返回 false
 */
bool IsFull(Stack S)
{
	bool answer = false;
	if(S->Top == S->MaxSize-1) {
		answer = true;
	}
	return answer;
}

/* 判断堆栈 S 是否位空
 * 若是返回 true，否则返回 false。
 */
bool IsEmpty(Stack S)
{
	bool answer=false;
	if(S->Top==-1) {
		answer = true;
	}
	return answer;
}


/* 将元素 X 压入堆栈。
 * 若堆栈已经满，返回 false；
 * 否则将元素 X 插入到堆栈 S 的顶处并返回true。
 */
bool Push(Stack S, ElementType X)
{
	bool answer = true;
	if(IsFull(S)) {
		answer = false;
	} else {
		S->Top += 1;
		S->Data[S->Top] = X;
	}
	return answer;
}

/* 删除并返回站定元素。
 * 若堆栈为空，返回错误信息。
 * 否则将栈顶元素从堆栈中删除并返回。
 */
ElementType Pop(Stack S)
{
	ElementType ERROR= 0X80000001;
	ElementType answer;
	if(IsEmpty(S)) {
		answer = ERROR;
	} else {
		answer = S->Data[S->Top];
		S->Top -= 1;
	}
	return answer;
}
