/* 堆栈的链式存储实现
 * 栈的练市存储结构（链栈）与单链表相似，但其操作受限制，插入和删除操作
 * 只能在链栈的栈顶进行。栈顶指针Top 就是链表的头指针。有时为了简化算法，
 * 链栈也可以带一空的表头结点，表头结点后面的第一个结点就是链栈的栈顶结点，
 * 栈中其他结点通过他们的指针Next 链接起来，栈底结点的 Next 为 Null。
 * 
 * 参考文献 数据结构（第2版） 主编 陈越 编著 和钦铭
 * 作者 Lin Liu
 * Date April 28, 2019
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;
typedef struct SNode * PtrToSNode;
struct SNode{
	ElementType Data;
	PtrToSNode Next;
};
typedef PtrToSNode Stack;

Stack CreateStack();
bool IsEmpty(Stack S);
bool Push(Stack S, ElementType X);
ElementType Pop(Stack S);

int main(int argc, int argv[])
{

	Stack S = CreateStack();
	int i;
	printf("\n%s\n", "PUSH");
	for (i=0; i<100; i++) {
		printf("%i\t", Push(S, i*i));
	}
	printf("\n%s\n", "POP");
	for (;i>-1;i--) {
		printf("%i\t", Pop(S));
	}
	return 0;
}

/* 创建一个带非空头结点的链栈, 注意，非空头结点
 * 并返回头结点
 **/
Stack CreateStack()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = -1111111111;
	S->Next = NULL;
	return S;
}

/* 判断栈链是否位空
 * 若空，返回true
 * 否则，返回false
 */
bool IsEmpty(Stack S)
{
	bool answer = false;
	//这里必须加上 ==NULL 否则就会报错!!!
	if (S->Next==NULL) {
		answer = true;
	} 
	return answer;
}

/* 向堆栈 S 压入元素 X 到栈顶
 * 若成功，返回true
 */
bool Push(Stack S, ElementType X)
{
	Stack cache = (Stack)malloc(sizeof(struct SNode));
	cache->Data = X;
	cache->Next = S->Next;
	S->Next = cache;
	return true;
}


/* 弹出一个元素
 * 如果 S 空，返回错误信息
 * 否则，返回栈顶元素
 */
ElementType Pop(Stack S)
{
	ElementType	ERROR = 0X80000001;
	ElementType answer;
	if (IsEmpty(S)) {
		printf("%s\n", "链栈为空");
		answer = ERROR;
	} else {
		Stack cache = S->Next;
		answer = cache->Data;
		S->Next = cache->Next;
		free(cache);
	} 
	
	return answer;
}

