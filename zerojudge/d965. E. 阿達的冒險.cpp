#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 2001
short C[N+1][N+1], Next[N+1], Last[N+1];
typedef struct {
	int x, in;
}Sequence;
Sequence A[N];
int cmp1(const void *i, const void *j) {
	Sequence *a, *b;
	a = (Sequence *)i, b = (Sequence *)j;
	return a->x - b->x;
}
int cmp2(const void *i, const void *j) {
	Sequence *a, *b;
	a = (Sequence *)i, b = (Sequence *)j;
	return a->in - b->in;
}
void Modify(short *C, int n, int L, int v) {
	while(n <= L) {
		C[n] = C[n] > v ? C[n] : v;
		n = Next[n];
	}
}
int Query(short *C, int n) {
	static short max;
	max = 0;
	while(n) {
		max = max > C[n] ? max : C[n];
		n = Last[n];
	}
	return max;
}
main() {
	int T, n, i, j, tmp;
	for(i = 1; i <= N; i++)
		Next[i] = i+(i&(-i)), Last[i] = i-(i&(-i));
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(i = 1; i <= n; i++)
			scanf("%d", &A[i].x), A[i].in = i;
		A[0].x = -1, A[0].in = 0;
		qsort(A, n+1, sizeof(Sequence), cmp1);
		int New = 1, last = A[0].x;
		for(i = 0; i <= n; i++) {
			if(last != A[i].x)
				last = A[i].x, New++;
			A[i].x = New;
		}
		qsort(A, n+1, sizeof(Sequence), cmp2);
		memset(C, 0, sizeof(C));		
		int Ans = 1;
		for(i = 0; i <= n; i++) {
			for(j = 0; j < i; j++) {
				tmp = Query(C[j], A[i].x-1) + (i != 0);
				Modify(C[i], A[j].x, New, tmp);
				Modify(C[j], A[i].x, New, tmp);
				Ans = Ans > tmp ? Ans : tmp;
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
