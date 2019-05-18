#include <stdio.h>
#include <stdlib.h>
#define MAXMATRIXSIZE 20

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
	for(i=0; i<MAXMATRIXSIZE;i++){
		for(j=0;j<MAXMATRIXSIZE;j++) {
			printf("%i ",Maze[i][j]);
		}
		printf("\n");
	}

	return 0;
}

