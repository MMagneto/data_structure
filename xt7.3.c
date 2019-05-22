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
		cnt = N;
		lastnum = 0;
		currentnum = 0;
		for(i=0;i<N;i++) {
			scanf("%d", &seq[i]);
		}
		for(i=0;i<0;i++ ) {
			if(currentnum<lastnum) {
				//��һ�� Pop �������У���ǰ��Ӧ�ñ���һ����С1
				subseqcnt++;
				if(currentnum<subseqMax && currentnum != lastnum-1 ) {
					tag = 1;
				}
			} else if(currentnum>lastnum) {
				//������������������������������
				subseqcnt = 0;
				if(subseqMax>currentnum) {
					subseqMax = currentnum;
				}
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

		
