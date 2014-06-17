#include<stdio.h>
int Sum, A[1000], T[1000];
int Merge(int l, int m, int r) {
	int in1 = l, in2 = m+1;
	int i, j, top = 0, tmp = 0;
	while(in1 <= m && in2 <= r) {
		if(A[in1] <= A[in2])
			T[top++] = A[in1++], Sum += tmp;
		else
			T[top++] = A[in2++], tmp++;
	}
	while(in1 <= m)	T[top++] = A[in1++], Sum += tmp;
	while(in2 <= r)	T[top++] = A[in2++];
	for(i = 0, j = l; i < top; i++, j++)
		A[j] = T[i];
}
int MergeSort(int l, int r) {
	if(l < r) {
		int m = (l+r)/2;
		MergeSort(l, m);
		MergeSort(m+1, r);
		Merge(l, m, r);
	}
}
int main() {
	int i, N;
	while(scanf("%d", &N) == 1) {
		for(i = 0; i < N; i++)
			scanf("%d", &A[i]);
		Sum = 0;
		MergeSort(0, N-1);
		printf("Minimum exchange operations : %d\n", Sum);
	} 
    return 0;
}
