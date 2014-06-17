#include<stdio.h>
#include<stdlib.h>
#define oo 1000000000
int A[100001], flag;
int cmp(const void *i, const void *j) {
	return *(int *)i - *(int *)j;
} 
int Find_Median(long long n) {
	long long Gap = n*(n-1)/2, tmp1, tmp2;
	int l = 0, m, r = oo, i, flag = 0;
	int idx;
	Gap = Gap/2 + (Gap%2 != 0);
	do {
		m = (l + r)/2, tmp1 = 0, tmp2 = 0, flag = 0;
		idx = 0;
		for(i = 0; i < n; i++) {
			while(idx < n && A[idx]-A[i] <= m)	{
				if(A[idx]-A[i] == m)	flag = 1;
				idx++;
			}
			tmp1 += idx - i - 1;
		}
		if(flag) {
			idx = 0;
			for(i = 0; i < n; i++) {
				while(idx < n && A[idx]-A[i] < m)
					idx++;
				tmp2 += idx - i - 1;
			}
		}
		if(tmp1 >= Gap && tmp2 < Gap && flag != 0)	return m;
		if(tmp1 < Gap)	l = m+1;
		else	r = m-1;
	} while(l <= r);
}
int main() {
	int i, j, n, k = 0;
	while(scanf("%d", &n) == 1) {
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		qsort(A, n, sizeof(int), cmp);
		printf("%d\n", Find_Median(n));
	}
	return 0;
}
