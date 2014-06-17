#include<stdio.h>
#include<stdlib.h>
int Used[10] = {};
void DFS(int Idx, int sum) {
	if(Idx == 10) {
		printf("%d\n", sum);
		return ;
	}
	int i;
	for(i = 1, sum *= 10; i < 10; i++)
		if(!((sum+i)%Idx) && !Used[i]) {
			Used[i] = 1;
			DFS(Idx+1, sum+i);
			Used[i] = 0;
		}
}
main() {
	DFS(1, 0);
	return 0;
}
