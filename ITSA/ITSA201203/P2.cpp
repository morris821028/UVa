#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int n, A[20], used[20];
int flag;
void DFS(int len, int goalseg, int sum, int seg, int last) {
	if(sum > len || flag == 1)	return;
	if(sum == len) {
		DFS(len, goalseg, 0, seg+1, 0);
		return;
	}
	if(seg == goalseg) {
		flag = 1;
		printf("%d %d\n", len, goalseg);
		return;
	}
	int i;
	for(i = last; i < n; i++) {
		if(used[i] == 0) {
			used[i] = 1;
			DFS(len, goalseg, sum+A[i], seg, i+1);
			used[i] = 0;
		}
	}
}
int main() {
	int t, i;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int min = 0, sum = 0;
		for(i = 0; i < n; i++) { 
			scanf("%d", &A[i]);
			if(min < A[i])	min = A[i];
			sum += A[i];
		} 
		flag = 0;
		for(i = min; ; i++) {
			if(sum%i == 0)
				DFS(i, sum/i, 0, 0, 0);
			if(flag == 1)	break;
		}
	}
    return 0;
}/*
3
7
2 23 48 5 25 25 22
4
6 2 5 1
20
1 13 11 15 4 17 8 23 7 8 9 5 19 5 6 29 2 2 2 24
*/
