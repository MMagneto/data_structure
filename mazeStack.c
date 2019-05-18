/* 通过栈来解决迷宫问题 */


#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define MAXMATRIXSIZE 20	/*迷宫矩阵最大行列数*/
#define MAXSTACKSIZE 100	/*堆栈最大规模*/

struct Offsets {	/*偏移量结构dingyi*/
	int Vert;	/*纵向偏移*/
	int Horiz;	/*横向偏移*/
};

struct MazePosition { /*迷宫中的位置结构*/
	int Row;	/*行号*/
	int Col;	/*列号*/
	int Dir;	/*对应偏移量数组的方向号*/
};

typedef struct MazePosition ElementType;
ElementType ERROR = {.Row=0x8000001, .Col=0x80000001, .Dir=0x80000001};
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
void Path(int Maze[][MAXMATRIXSIZE], int EXITROW, int EXITCOL);

void Path(int Maze[][MAXMATRIXSIZE], int EXITROW, int EXITCOL)
{
	/* 默认迷宫Maze 的入口为(1,1), 出口为(EXITROW, EXITCOL)*/
	/*迷宫8个刚想的偏移量数组*/
	struct Offsets Move[8] = 
	{{-1,0}, {-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
	Stack S;	/*辅助求解的堆栈*/
	int Mark[MAXMATRIXSIZE][MAXMATRIXSIZE];	/*标记位置是否走过*/
	/*初始化 Mark */
	for( int i=0;i<MAXMATRIXSIZE;i++){
		for(int j=0;j<MAXMATRIXSIZE;j++) {
			if(i==0 || j==0 || i==MAXMATRIXSIZE-1 || j==MAXMATRIXSIZE-1) {
				Mark[i][j] = 1;
			} else {
				Mark[i][j] = 0;
			}
		}
	}
	

	struct MazePosition P;
	int Row, Col, NextRow, NextCol, Dir;
	bool Found = false;

	S = CreateStack();	/*初始化空栈*/
	Mark[EXITROW][EXITCOL] = 1;	/*从出口位置开始，标记位走过*/
	/*将出口及下一个位置放入堆栈*/
	P.Row = EXITROW;
	P.Col = EXITCOL;
	P.Dir = 0;
	Push(S, P);

	while(!IsEmpty(S) && !Found) { /*当栈非空且没找到入口时*/
		P=Pop(S);	/*取出栈顶元素为当前位置*/
		Row = P.Row;
		Col = P.Col;
		Dir = P.Dir;
		while(Dir<8 && !Found) {/*当还有方向可探入，且没找到入口时*/
			/*尝试往下一个方向 Dir 移动*/
			NextRow = Row + Move[Dir].Vert;
			NextCol = Col + Move[Dir].Horiz;
			if(NextRow == 1 && NextCol ==1) {
				/*如果到达入口*/
				Found = true;
			} else {	/*下一个位置不是出口*/
				/*如果下一个位置可通过，且没走过*/
				if(!Maze[NextRow][NextCol] && !Mark[NextRow][NextCol]) {
					Mark[NextRow][NextCol] = 1;	/*标记为走过*/
					/*当前位置和下一个方向存入栈*/
					P.Row = Row;
					P.Col = Col;
					P.Dir = Dir + 1;
					//显示路径
//					for(int i=0; i<MAXMATRIXSIZE; i++) {
//						for(int j=0;j<MAXMATRIXSIZE;j++) {
//							if(i==Row && j==Col) {
//								printf("%s ", "*");
//							} else {
//								printf("%i ", Maze[i][j]);
//							}
//						}
//						printf("\n");
//					}
//					for(int i=0; i<MAXMATRIXSIZE;i++) {
//						printf("\b\r");
//					}
//					for(int i=0; i<MAXMATRIXSIZE;i++) {
//						printf("\b");
//					}
//					sleep(1);
//

					Push(S,P);
					printf("%i, %i\n", Row, Col);
					/*更新当前位置，从方向0开始*/
					Row = NextRow;
					Col = NextCol;
					Dir = 0;
				} else {
				/*若此路不通，尝试下一个位置*/
					++Dir;
				}
			}
		}/*结束 8 方向探测*/
	}/*结束搜索*/
	if(Found) { /*找到一个路径，并输出该路径*/
		printf("找到路径如下\n");
		printf("行 列\n");
		printf("1 1\n");/*打印入口*/
		printf("%d %d\n",Row, Col);/*不要忘记最后一步位入堆栈*/
		
		ElementType road[3*MAXMATRIXSIZE];
		int i=0;
		while(!IsEmpty(S)){
			P = Pop(S);
			road[i++] = P;
			printf("%d %d\n", P.Row, P.Col);
		}

		//显示路径
		for(int i=0; i<MAXMATRIXSIZE; i++) {
			for(int j=0;j<MAXMATRIXSIZE;j++) {
				int tag = 1;
				for (int k=0;k<3*MAXMATRIXSIZE;k++) {
					if(i==road[k].Row && j==road[k].Col) {
						tag = 0;
						printf("%s ", "*");
						break;
					} 
				}
				if (tag == 1) {
						printf("%i ", Maze[i][j]);
				}
					
					
			}
				printf("\n");
		}

	} else {/*若没找到路径*/
		printf("该迷宫无解。\n");
	}
}

int main(int argc, int argv[])
{
	int Maze[MAXMATRIXSIZE][MAXMATRIXSIZE];
	/*初始化迷宫*/
	int i, j;
	for(i=0; i<MAXMATRIXSIZE;i++){
		for(j=0;j<MAXMATRIXSIZE;j++) {
			if(i==0 || j==0 || i==MAXMATRIXSIZE-1 || j==MAXMATRIXSIZE-1) {
				/*边界上的位置设为 1 */
				Maze[i][j] = 1;
			} else {/*非边界位置*/
				if (i==1 && j==1) { /*入口*/
					Maze[i][j] = 1;
				} else { /*非入口*/
				//	srand((unsigned)time(NULL));
					Maze[i][j] = rand()%2; 				}
			}
		}
	}
	printf("*** 迷宫形状 ***\n");
	for(i=0; i<MAXMATRIXSIZE;i++){
		for(j=0;j<MAXMATRIXSIZE;j++) {
			printf("%i ",Maze[i][j]);
		}
		printf("\n");
	}
	int EXITROW = 19;
	int EXITCOL = 8;
	Path(Maze, EXITROW, EXITCOL);

	return 0;
}

/* 创建一个带非空头结点的链栈, 注意，非空头结点
 * 并返回头结点
 **/
Stack CreateStack()
{
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->Data = ERROR;
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
	if (IsEmpty(S)==true) {
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

