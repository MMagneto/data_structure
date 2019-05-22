#include <stdio.h>

int main()
{
	int N,  M;
	scanf("%d %d\n", &N, &M);
	if(M>50) {
		printf("NO\n");
		return 0;
	} else {
	char line[101];
	char *p;
	int  tag, count;
	while(N--) {
		count = 0;
		tag = 0;
		fgets(line, 101, stdin);
		p = line;
		while(*p) {
			if(*p == 'S' ) {
				count++;
			} else if(*p == 'X') {
				count--;
			}
			if(count<0 || count>M) {
				tag = 1;
				break;
			}
			p++;
		}
		if(count==0 && tag == 0) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	
	return 0;
	}
}
