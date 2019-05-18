/* 本文档使用链表实现了线性表的存储
 * 参考文献：
 *			《数据结构》第2版， 主编 陈越
 * 作者 刘林
 * 日期 April 27, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType; 
typedef struct LNode *PtrToLNode;
struct LNode {
	ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position; //这里的位置是结点的地址
typedef PtrToLNode List;

List MakeEmpty();
ElementType FindKth(List L, int i);
Position Find(List L, ElementType X);
List Insert(List L, ElementType X, int i);
List Delet(List L, int i);
int Length(List L);

int main(int argc, const char* argv[])
{
	List L;
	L = MakeEmpty();
	int length = Length(L);
	printf("length=%d\n", length);
	L = Insert(L, 5, 1);
	L = Insert(L, 7, 2);
	L = Insert(L, 7, 1);
	length = Length(L);
	printf("length=%d\n", length);
	for (int i=0;i<Length(L);i++) {
		printf("第%i个数据是：%d\n", i+1, FindKth(L,i+1));
	}	

	return 0;
}

/*初始化一个新的空线性表链表*/
List MakeEmpty()
{
	List L=NULL; //让List的指针指向NULL
	return L;
}

/* 返回线性表 L 的长度 */
int Length(List L)
{
	int length=0;
	while(L){
		length ++;
		L = L->Next;
	}
	return length;
}

/*按元素查找线性表中的元素，并返回元素所在位置*/
Position Find(List L, ElementType X)
{
	Position pst = NULL;
	while(L) {
		if (X == L->Data ) {
			pst = L;
			break;
		}
		L = L->Next;
	}
	return pst;
}

/* 在位置 i 插入一个元素，如果成功，返回true，否则返回false */
List Insert(List L, ElementType X, int i)
{
	List answer=L;
	int count = 1;
	//插在表头
	if (i==1) {
		List cache = (List)malloc(sizeof(struct LNode));
		cache->Data = X;
		cache->Next = L;
		answer = cache;
	} else {
		//插在非表头
		while(L) {
			if (i == count+1) {
				//查找到 i-1 的结点
				List cache = (List)malloc(sizeof(struct LNode));
				cache->Data = X;
				cache->Next = L->Next;
				L->Next = cache;
				break;
			}
			count ++;
			L = L->Next;
		}
	}

	if (L == NULL && i!=1) {
		//如果指针 L 移到了线性表链表的结尾，且插入的位置不是表头
		printf("%s\n", "输入的位置太大");
	}
	return answer;
}

/* 返回第 i 个元素 */
ElementType FindKth(List L, int i)
{ 
	ElementType answer=0X80000001;
	int count = 1;
	while(L && count++!=i) {
		L = L->Next;
	}
	if(L) {
		answer = L->Data;
	}
	return answer;
}


/* 删除第 i 个元素 */
List Delet(List L, int i)
{
	List answer=L;
	int count = 1;
	while( L ) {
		if (count+1 == i) {
			List cache = L->Next;
			L->Next = cache->Next;
			free(cache);
			break;
		}
		count++;
		L = L->Next;
	}
	return answer;
}
