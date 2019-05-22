#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
struct Node {
	int Data;
	int Next;
};
typedef PtrToNode List;
int MAXN = 100001;

void PrintLNode(List L);
void Reverse(List L,int N, int K);

int main(int argc, const char *argv[])
{
	int N, K;
	int Address, Data, Next;
	struct Node L[MAXN]; 
	//List L = (List)malloc(MAXN*sizeof(struct Node));;

	scanf("%d", &L[MAXN-1].Next);
	scanf("%d", &N);
	scanf("%d", &K);
	int cnt = N;
	while(cnt--) {
		scanf("%d", &Address);
		scanf("%d", &L[Address].Data);
		scanf("%d", &L[Address].Next);
	}
//	printf("\nbefore\n");
//	PrintLNode(L);
//	printf("\nafter\n");
	Reverse(L,N, K);
	PrintLNode(L);


	return 0;
}

void PrintLNode(List L) {
	int P = L[MAXN-1].Next; 
	while(L[P].Next!=-1) {
		printf("%05d %d %05d\n", P, L[P].Data, L[P].Next);
		P = L[P].Next;
	}
	printf("%05d %d %d\n", P, L[P].Data, L[P].Next);

}

void Reverse(List L,int N, int K) {
	int P = L[MAXN-1].Next;
	int newP;
	int new, old, tmp;
	new = P;
	old = L[new].Next;
	tmp = L[old].Next;
	int cnt = K;
	int tag = 0;
	while(--cnt) {
		L[old].Next = new;
		new = old;
		old = tmp;
		tmp = L[tmp].Next;
		if(L[tmp].Next==-1) {
			tag = 1;
		}
	}
	L[P].Next = old;
	L[MAXN-1].Next = new;
	new = old;
	old = tmp;
	tmp = L[tmp].Next;
	N = N - K;
	while(N-K>=0 && tag == 0) {
		cnt = K;
		while(--cnt) { 
			L[old].Next = new;
			new = old;
			old = tmp;
			tmp = L[tmp].Next;
			if(L[old].Next == -1) {
				tag = 1;
			}
		}
		newP = L[P].Next;
		L[P].Next = new;
		P = newP;
		L[P].Next = old;
		N -= K;
		new = old;
		old = tmp;
		tmp = L[old].Next;


	}

}

