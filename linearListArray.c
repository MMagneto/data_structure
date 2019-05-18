#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 本文档利用数组实现一个线性表
 * 参考文献：	《数据结构》(第2版) 
 *				主编 陈越 编著 何钦铭 陈镜春 魏宝刚 杨枨
 * 日期 April 21, 2019
 * auther Lin Liu
 */
#define MAXSIZE 100
typedef int Position;
/*这里的位置就是数组的整型下标，从0开始。
 */
typedef int ElementType; //线性表的类型

typedef struct LNode *PtrToLNode;
struct LNode{
	ElementType Data[MAXSIZE];
	Position Last;
};
typedef PtrToLNode List;


/*---------begin----------函数声明---------begin---------*/
List MakeEmpty();
ElementType FindKth(List L, int i);
Position Find( List L, ElementType X);
bool Insert ( List L, ElementType X, int i);
bool Delete(List L, int i);
int Length(List L);
bool Save(List L);
/*----------end---------函数声明----------end----------*/

/* ----------begin-------主函数-----------begin----------*/
int main(int agrc, const char* argv[])
{

	List l = MakeEmpty();
	bool ins;
	bool wrt;
	printf("%p\t:%p\t:%p\n", l, &l->Data[0], &l->Last);
	ins = Insert(l, 3, 1);
	printf("%d\t, length = %d\n", ins, Length(l));
	ins = Insert(l, 51, 2);
	printf("%d\t, length = %d\n", ins, Length(l));
	ins = Insert(l, 287, 3);
	printf("%d\t, length = %d\n", ins, Length(l));
	wrt = Save(l);
	printf("%d\n", wrt);
	return 0;
}



















/* ----------end-------主函数-----------end----------*/

/*---------begin--------- 函数定义----------begin----------*/
//初始化
List MakeEmpty(){
	List L;
	L = (List)malloc(sizeof(struct LNode));
	L->Last = -1;
	return L;
}

//根据指定的位序，返回L 中相应的元素a[i]。
ElementType FindKth(List L, int i){
	ElementType answer = ~(unsigned int)0 /2;
	if(L->Last == -1) {
		printf("%s\n", "线性表为空\n");
	} else if (i <= 0 ) {
		printf("%s\n", "索引错误\n");
	} else if ( i > L->Last+1 ) {
		printf("%s\n", "索引超出线性表范围\n");
	}
	return answer;
}	

	
//已知X, 返回线性表 L 中与 X 相同的第一个元素的位置；
//若不存在则返回错误信息
Position Find( List L, ElementType X) {
	Position answer = -1;
	int i;
	if(L->Last == -1) {
		printf("%s\n", "线性表为空\n");
	} else {
		for (i=0; i<L->Last; i++) {
			if ( L->Last == X) {
				answer = i+1;
				break;
			}
		}
		if (i==L->Last) {
			printf("%s\n", "未找到");
		}
	}
	return answer;
}
		
//在 L 的指定位序 i 前插入一个新元素 X ；
//成功返回 true, 否则返回 false;
bool Insert ( List L, ElementType X, int i) {
	bool answer = false;
	if ( i<=0 ) {
		printf("%s\n", "error: 指定序列必须为正整数！");
	} else if ( i > L->Last + 2) {
		printf("%s\n", "指定的位置超过数组长度");
	} else if (L->Last == MAXSIZE) {
		printf("%s\n", "顺序表已满");
	} else if ( i>0 && i< L->Last+2 ) {
		for (int j=L->Last;j>i-1; j--) {
			L->Data[j] = L->Data[j-1];
		}
		L->Data[i-1] = X;
		L->Last += 1;
		answer = true;
	} else if(i = L->Last+2) {
		L->Data[i-1] = X;
		L->Last += 1;
		answer = true;
	}
	return answer;
}

//从 L 中删除指定位序 i 的元素；成功返回 true，否则返回 false。
bool Delete(List L, int i) {
	bool answer = false;
	if ( i<=0 ) {
		printf("%s\n", "error: 指定序列必须为正整数！");
	} else if ( i > L->Last + 1) {
		printf("%s\n", "指定的位置超过数组长度");
	} else if ( i>0 && i<L->Last) {
		for (int j=i-1; j<L->Last+1;j++){
			L->Data[j] = L->Data[j+1];
		}
		L->Last -= 1;
		answer = true;
	}
	return answer;
}
	
//返回线性表 L 的长度。
int Length(List L) {
	return L->Last+1;
}

bool Save(List L) {
	FILE *fp = fopen("./linearArray.txt", "wb");
	bool answer = false;
	if (fp) {
// 二进制方式写入	
//		for (int i=0; i<L->Last+1; i++) {
//			if(fwrite(&L->Data[i], sizeof(ElementType), 1, fp)!=1) {
//				printf("%s\n", "写入数据错误!");
//			} else {
//				answer = true;
//			}
//		}

//	二进制方式写入
		if (fwrite(&L->Data, sizeof(ElementType), L->Last+1, fp)!= L->Last+1) {
			printf("%s\n", "写入数据发生错误");
		} else {
			answer = true;
		}
	//	文本方式写入
//		for (int i=0; i<L->Last+1; i++) {
//			fprintf(fp,"%i\t%i\n",i,  L->Data[i]);
//			answer = true;
//		}
	} else {
		printf("%s\n", "文件打开错误");
	}

	fclose(fp);
	return answer;
}
/*--------end--------- 函数定义----------end--------*/
