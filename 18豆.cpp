#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int A[4];
int Ans[20] = {};
/*
	[] = {null, 豹子, 重來, 3, 4, 5, ...}
*/
int cmp(const void *i, const void *j) {
	return *(int *)i - *(int *)j;
}
void toCheck() {
	int C[4];
	memcpy(C, A, sizeof(C));
	qsort(C, 4, sizeof(int), cmp);
	if(C[0] == C[3]) {
		Ans[1]++;
		return;
	} 
	if(C[0] == C[2] || C[1] == C[3]) {
		Ans[2]++;
		return;
	}
	if(C[0] == C[1]) {
		Ans[C[2]+C[3]]++;
		return;
	}
	if(C[2] == C[3]) {
		Ans[C[0]+C[1]]++;
		return;
	}
	if(C[1] == C[2]) {
		Ans[C[0]+C[3]]++;
		return;
	}
	Ans[2]++;
}
void DFS(int idx) {
	if(idx == 4) {
		toCheck();
		return;
	}
	int i;
	for(i = 1; i <= 6; i++) {
		A[idx] = i;
		DFS(idx+1);
	}
}
void Print() {
	int i;
	for(i = 3; i <= 12; i++)
		printf("%2d : %3d\n", i, Ans[i]);
	printf("豹子 : %3d\n", Ans[1]);
	printf("重來 : %3d\n", Ans[2]);
	system("pause");
}
int main() {
	DFS(0);
	Print(); 
    return 0;
}
