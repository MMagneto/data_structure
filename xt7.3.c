/* Pop Sequence */

#include <stdio.h>

int main(int argc, const char *argv[]) {
	int M, N, K, i;
	int cnt;
	int tag;
	int lastnum;
	int subseqcnt=0, currentnum, subseqMax;
	scanf("%d", &M);
	scanf("%d", &N);
	scanf("%d", &K);
	int seq[N];

	while(K--) {
		for(i=0;i<N;i++) {
			scanf("%d", &seq[i]);
		}
		tag = 0;
		subseqcnt = 1;
		subseqMax = seq[0];
		currentnum = seq[0];
		for(i=1;i<N;i++ ) {
			lastnum = currentnum;
			currentnum = seq[i];
			if(currentnum<lastnum) {
				subseqcnt++;
			} else if(currentnum>lastnum && currentnum>subseqMax)  {
				//如果新数大于老数,且大于之前出现过的所有的数
				//则出现了新序列
				subseqcnt = 1;
				subseqMax = currentnum;
			} else if(currentnum >lastnum && currentnum<subseqMax ) {
				tag = 1;
			}
			if(subseqcnt>M) {
				tag = 1;
			}
		}
		if(tag == 1) {
			printf("NO\n");
		} else {
			printf("YES\n");
		}
	}

	return 0;
}

		
