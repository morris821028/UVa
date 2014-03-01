#include <stdio.h>
#include <stdlib.h>
void findLIS(int N, int LIS[], int pos[], int A[]) {
	int i, L = -1, l, r, m, newSet;
	int j;
	for(i = 0; i < N; i++) {
		l = 0, r = L, newSet = -1;
		while(l <= r) {
			m = (l+r)/2;
			if(pos[m] <= A[i]) {
				if(m == L || pos[m+1] > A[i]) {
					newSet = m+1;break;
				} else
					l = m+1;
			} else {
				r = m-1;
			}
		}
		if(newSet == -1)	newSet++;
		pos[newSet] = A[i];
		LIS[i] = newSet+1;
		if(L < newSet)	L = newSet;
	}
}
void findLDS(int N, int LDS[], int pos[], int A[]) {
	int i, L = -1, l, r, m, newSet;
	int j;
	for(i = 0; i < N; i++) {
		l = 0, r = L, newSet = -1;
		while(l <= r) {
			m = (l+r)/2;
			if(pos[m] >= A[i]) {
				if(m == L || pos[m+1] < A[i]) {
					newSet = m+1;break;
				} else
					l = m+1;
			} else {
				r = m-1;
			}
		}
		if(newSet == -1)	newSet++;
		pos[newSet] = A[i];
		LDS[i] = newSet+1;
		if(L < newSet)	L = newSet;
	}
}
int main() {
	int T, N, i;
	int A[2001], LDS[2001], LIS[2001], pos[2001];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		for(i = 0; i < N; i++)
			scanf("%d", &A[N-i-1]);
		findLIS(N, LIS, pos, A);
		findLDS(N, LDS, pos, A);
		int max = 0;
		for(i = 0; i < N; i++) {
			if(LIS[i]+LDS[i]-1 > max) 
				max = LIS[i]+LDS[i]-1;
		}
		printf("%d\n", max);
	}
    return 0;
}
