#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int v, times;
}DICE;
DICE Dice[6];
int A[4], Ans[13] = {};
/*[] = {null, 4-same, retart, 3, 4, 5, ...}*/
int cmp(const void *i, const void *j) {
	DICE *a, *b;
	a = (DICE *)i, b = (DICE *)j;
	if(a->times != b->times)
		return b->times - a->times; /*increasing*/
	return a->v - b->v;
}
void toCheck() {
	int i;
	for(i = 0; i < 6; i++) /*init*/
		Dice[i].v = i+1, Dice[i].times = 0;
	for(i = 0; i < 4; i++)
		Dice[A[i]-1].times++;
	qsort(Dice, 6, sizeof(DICE), cmp);
	if(Dice[0].times == 4)
		Ans[1]++;
	else if(Dice[0].times == 3)
		Ans[2]++;
	else if(Dice[0].times == 2) {
		int tmp;
		tmp = Dice[1].times*Dice[1].v+Dice[2].times*Dice[2].v;
		Ans[tmp]++;
	}
	else 
		Ans[2]++;
}
void DFS(int idx) {
	if(idx == 4) {
		toCheck();
		return;
	}
	for(int i = 1; i <= 6; i++) {
		A[idx] = i;
		DFS(idx+1);
	}
}
void Print() {
	int i;
	for(i = 3; i <= 12; i++)
		printf("%2d : %3d\n", i, Ans[i]);
	printf("4-same : %3d\n", Ans[1]);
	printf("restart : %3d\n", Ans[2]);
	system("pause");
}
int main() {
	DFS(0);
	Print(); 
    return 0;
}
