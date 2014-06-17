#include<stdio.h>
#include<string.h>
int SparseTable[100000][20];
int BinaryExpFloor(int n) {
	return (int)floor(log10(n)/log10(2));
}
int Max(int x, int y) {
	return x > y ? x : y;
}
int Leftmost[100000], Rightmost[100000];
int Build(int *A, int n) {
	int i, j, k, t;
	int tmp = 0, before = A[0];
	for(i = 0; i < n; i++) {
		if(A[i] == before)	tmp ++;
		else {
			j = i-1;
			while(j >= 0 && A[i-1] == A[j])	SparseTable[j--][0] = tmp;
			tmp = 1;
		}
		before = A[i];
	}
	j = i-1;
	while(j >= 0 && A[i-1] == A[j])	SparseTable[j--][0] = tmp;
	Leftmost[0] = 0, Rightmost[n-1] = n-1;
	for(i = 1; i < n; i++)
		if(A[i] == A[i-1])	Leftmost[i] = Leftmost[i-1];
		else	Leftmost[i] = i;
	for(i = n-2; i >= 0; i--)
		if(A[i] == A[i+1])	Rightmost[i] = Rightmost[i+1];
		else	Rightmost[i] = i;
	for(k = 1, t = 2; t < n; k++, t <<= 1)
		for(i = 0; i+t <= n; i++)
			SparseTable[i][k] = Max(SparseTable[i][k-1], SparseTable[i+(t>>1)][k-1]);
}
int query(int i, int j, int *A) {
	int ni, nj, k, Ans = 0;
	ni = Rightmost[i]+1, nj = Leftmost[j]-1;
	if(ni <= nj) {
		k = BinaryExpFloor(nj-ni+1);
		Ans = Max(SparseTable[ni][k], SparseTable[nj-(1<<k)+1][k]);
		Ans = Max(Max(Ans, (ni-1)-i+1), j-(nj+1)+1);
	} else {
		if(A[i] != A[j])
			Ans = Max(ni-i, j-nj);
		else
			Ans = j-i+1;
	}

	return Ans;
}
int main() {
	int n, q, A[100000], i, x, y;
	while(scanf("%d", &n) == 1 && n) {
		scanf("%d", &q);
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		Build(A, n);
		while(q--) {
			scanf("%d %d", &x, &y);
			printf("%d\n", query(x-1, y-1, A));
		}
	}
    return 0;
}
