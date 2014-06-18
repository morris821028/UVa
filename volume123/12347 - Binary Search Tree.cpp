#include<stdio.h>
#define L 10000
int SparseTable[L][15], A[L]; /*2^14 = 16384 >= L*/
int Max(int x, int y) {
	return x > y ? x : y;
}
int Build(int *A, int n) {
	int i, t, k;
	for(i = 0; i < n; i++)
		SparseTable[i][0] = A[i];
	for(k = 1, t = 2; t <= n; k++, t <<= 1)
		for(i = 0; i+t <= n; i++)
			SparseTable[i][k] = Max(SparseTable[i][k-1], SparseTable[i+(t>>1)][k-1]);
}
void PostOrder(int i, int n) {
	int k, t, st = i, cut;
	if(i > n)	return;
	while(1) {
		cut = -1;
		for(k = 1, t = 2; st+t <= n; k++, t <<= 1)
			if(SparseTable[st][k] > SparseTable[st][0]) {
				cut = 1;
				break;
			}
		if(SparseTable[st][0] > SparseTable[i][0])
			{cut = 0;break;}
		if(cut == -1 && st > n)	break;
		st = st + (t>>1);
	}
	
	if(cut != -1) {
		PostOrder(i+1, st-1);
		PostOrder(st, n);
	} else {
		PostOrder(i+1, n);
	}
	printf("%d\n", A[i]);
}
int main() {
	int i = 0;
	while(scanf("%d", &A[i]) == 1)
		i++;
	Build(A, i);
	PostOrder(0, i-1);
    return 0;
}
