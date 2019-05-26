
/* 堆，用数组存放，下表 1 开始 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 1001
#define MINH -10001

typedef int *MinHeap;
int H[MAXN], size; /*用数组表示堆, size 为当前堆的大小*/

void CreateHeap(){
	size = 0;
	H[0] = MINH;
	/*设置"岗哨"*/
}

bool IsFull() {
	if(size == MAXN-1 ) return true;
	else return false;
}

void Insert(int X) {
	/*将 X 插入 H */
	int i;
	if(IsFull(H)==false) {
		for(i=++size;H[i/2] >X; i/=2) {
			H[i] = H[i/2];
		}
		H[i] = X;
	}
}

int main(int argc, const char *argv[])
{
	int n,m,x,i,j;
	scanf("%d %d", &n, &m);
	CreateHeap(); /*堆初始化*/
	for(i=0;i<n; i++) { /*以逐个插入方式建堆*/
		scanf("%d", &x);
		Insert(x);
	}

	for(i=0;i<m;i++) {
		scanf("%d", &j);
		printf("%d", H[j]);
		while(j>1) { /*沿根方向输出各结点*/
			j/=2;
			printf(" %d", H[j]);
		}
		printf("\n");
	}

	return 0;
}
