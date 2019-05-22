#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char* ElementType;
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
//{{[}}

int main(int argc, int argv[])
{

	Stack S = CreateStack();
	Stack S0 = CreateStack();
	int i;
	char line[100];
	ElementType data;
	char *p;
	int tag = 0;
	do{
		fgets(line, 100, stdin);
		p = line;
		while(*p && tag == 0) {
			switch(*p) {
				case '(': Push(S,"("); break;
				case '[': Push(S,"[");break;
				case '{': Push(S, "{");break;
				case ')': { 
							  if(IsEmpty(S)) {
								  Push(S,")");
								  tag = 1;
							  } else {
								  data = Pop(S);
								  if(strcmp(data, "(")!=0) {
									 // Push(S, ")");
									  Push(S,data);
									  tag = 1;
								  }
							  }
							  break;
						  }
				case ']': {
							  if(IsEmpty(S)) {
								  Push(S, "]");
								  tag = 1;
							  } else {
								  data = Pop(S);
								  if(strcmp(data, "[") != 0) {
									 // Push(S, "]");
					                  Push(S, data);
									  tag = 1;
								  }
								
							  }
							  break;
						  }
				case '}': {
							  if(IsEmpty(S)) {
								  Push(S, "}");
								  tag = 1;
							  } else {
								  data = Pop(S);
								  if(strcmp(data, "{")!=0) {
								     // Push(S, "}");
								      Push(S,data);
									  tag = 1;
								  }
							  }
							  break;
						  }

				case '/': {
							  if(*p) {
								  p++;
								  if( *p=='*') {
									  Push(S, "/*");
								  }
							  }
							  break;
						  }
				case '*': {
							  if(*p) {
								 p++;
							 	 if( *p=='/') {
									 if(IsEmpty(S)) {
										 Push(S, "*/");
										 tag = 1;
									 } else {
										data = Pop(S);
										if(strcmp(data, "/*")!= 0) {
											// Push(S, "*/");
											 Push(S, data);
											 tag = 1;
										 }
								     }
								 }
							  }
							  break;
						  }
				default: break;
			}	
			if(*p) {
				p++;
			}
		}
		
	}while(strcmp(".\n", line)!=0);
	if(IsEmpty(S)) {
		printf("YES\n");
	} else {
		if(tag==0) {
			while(!IsEmpty(S)) {
				data = Pop(S);
			}
		} else {
			data = Pop(S);
		}
		printf("NO\n");
		switch (data[0]) {
			//如果栈顶是左括号
			case '(': 
			case '[':  
			case '{':
			case '/': printf("%s-?\n", data); break;
			//如果头上是个右括号
			case ')':
			case '}': 
			case ']': 
			case '*':   printf("?-%s\n", data); break;
			default: break;
			
		}

	}
	
	return 0;
}

/* 创建一个带非空头结点的链栈, 注意，非空头结点
 * 并返回头结点
 **/
Stack CreateStack()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
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
	ElementType answer;
	if (IsEmpty(S)) {
		printf("%s\n", "链栈为空");
		answer = "ERROR";
	} else {
		Stack cache = S->Next;
		answer = cache->Data;
		S->Next = cache->Next;
		free(cache);
	} 
	
	return answer;
}
