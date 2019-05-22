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
#include <string.h>

#define INFINITY 1e9/*代表正无穷*/
#define MAXOP 100

typedef int Position;
typedef double ElementType;
ElementType ERROR=INFINITY ;
typedef struct SNode * PtrToSNode;
struct SNode {
	ElementType *Data; /*存储元素的数组*/
	Position Top;		/*栈顶指针*/
	int MaxSize;		/*堆栈最大容量*/
};
typedef PtrToSNode Stack;
typedef enum {num, opr, end} Type;

Stack CreateStack(int Maxsize);
bool IsFull(Stack S);
bool Push(Stack S, ElementType X);
bool IsEmpty(Stack S);
ElementType Pop(Stack S);
ElementType PostExp(char *Expr);

Type GetOp(char *Expr, int *start, char* str);

char *MiddleToPost( char *Expr);

int main(int agrc, const char* argv[])
{
//	int i;
//	bool answer;
//	Stack S = CreateStack(100);
//	printf("\n%s\n", "PUSH");
//	for (i=0;i <100; i++) {
//		printf("%i\t", Push(S, i));
//	}
//	printf("\n%s\n", "POP");
//	for (;i>=0;i--) {
//		printf("%i\t", Pop(S));
//	}
	int n;
	ElementType f;
	char Expr[MAXOP];
	Stack S = CreateStack(100);
	fgets(Expr,MAXOP, stdin);
	f = PostExp(Expr);
	if(f<INFINITY) {
		printf("%.4f\n", f);
	} else {
		printf("%s\n", "表达式错误");
	}
	

	return 0;
}

char *MiddleToPost( char *Expr) {
	/*把中缀表达式转换成后缀表达式*/
	Stack S = CreateStack(2*MAXOP);
	char NewExpr[MAXOP];
	char *p = Expr;
	int i=0;
	/*跳过表达式前空格*/
	while((str[0]=Expr[(*start)++])==' ');
	while(*p)!='\0' && (*p)!='=') {
		switch(*p) {
			case '*': push(*p); NewExpr[i++]=' '; break;
			case '/': push(*p); NewExpr[i++]=' '; break;
			case '+': push(*p); NewExpr[i++]=' '; break;
			case '-': Push(*p); NewExpr[i++]=' '; break;









//计算一个后缀表达式的值
ElementType PostfixExp(char *Expr)
{
	/*调用 GetOp 函数读入后缀表达式并求值*/
	Stack S;
	Type T;
	ElementType Op1, Op2;
	char str[MAXOP];
	int start=0;
	/*申请一个新堆栈*/
	S = CreateStack(MAXOP);

	Op1 = Op2 = 0;
	while((T=GetOp(Expr, &start, str))!=end) {
		/*当未读到输入结束时*/
		if(T==num) {
			Push(S, atof(str));
		} else {
			if(!IsEmpty(S)) {
				Op2 = Pop(S);
			} else {
				Op2 = INFINITY;
			}
			if(!IsEmpty(S)) {
				Op1 = Pop(S);
			} else {
				Op2 = INFINITY;
			}
			switch(str[0]) {
			case '+': Push(S, Op1+Op2); break;
			case '*': Push(S, Op1*Op2); break;
			case '-': Push(S, Op1-Op2); break;
			case '/':
					  if(Op2 !=0.0 ) /*检查分母是否位0*/
						  Push(S, Op1/Op2);
					  else {
						  printf("错误：除法分母位零\n");
					  }
					  break;
			default:
					  printf("错误：未知运算符%s\n", str);
					  Op2 = INFINITY;
					  break;
			}
			if(Op2 >= INFINITY) break;
		}
	}
	if(Op2<INFINITY) /*如果处理完了表达式*/
		if(!IsEmpty(S)) /*而此时堆栈正常*/
			Op2 = Pop(S); /*记录计算结果*/
		else Op2 = INFINITY; /*否则标记错误*/
	free(S); /*释放堆栈*/
	return Op2;
}

Type GetOp(char *Expr, int *start, char *str) {
	/*从*start开始读入下一个对象( 操作数或运算符),
	 * 并保存在字符串str中
	 */
	
	 int i=0;
	 
	/*跳过表达式前空格*/
	while((str[0]=Expr[(*start)++])==' ');

	while(str[i]!=' ' && str[i] != '\0') {
		str[++i]=Expr[(*start)++];
	}
	if(str[i]=='\0') {/*如果读到输入的结尾*/
		(*start)--;
		/* *start指向结尾符*/
	}
	str[i]='\0'; /*结束一个对象的获取*/
	
	if(i==0) 
		return end; /*读到了结束*/
	/*如果str[0]是数字，或是符号跟个数字*/
	else if(isdigit(str[0]) || isdigit(str[1]))
		/*表示此时str存的是一个数字*/
		return num;
	else
		/* 表示此时存的是一个运算符*/
		return opr;
}

//bool isdigit(char c) {
//	if( c>='0' && c<='0') {
//		return true;
//	} else {
//		return false;
//	}
//}

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
	ElementType answer;
	if(IsEmpty(S)) {
		answer = ERROR;
	} else {
		answer = S->Data[S->Top];
		S->Top -= 1;
	}
	return answer;
}
