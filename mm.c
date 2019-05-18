#include <stdio.h>

int main()
{
	int i,j;
	int n=4;
	int matrix[4][4] = {0};
	for(i=0;i<n;i++) {
		for(j=0;j<n-1;j++) {
			scanf("%d ", &matrix[i][j]);
		}
		scanf("%d\n", &matrix[i][j]);
	}
}
