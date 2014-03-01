#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int dice[6];
}DICE;
void Right_turn(DICE *A) {
	static int t;
	t = A->dice[0], A->dice[0] = A->dice[4];
	A->dice[4] = A->dice[3], A->dice[3] = A->dice[1], A->dice[1] = t;
}
void Up_turn(DICE *A) {
	static int t;
	t = A->dice[0], A->dice[0] = A->dice[5];
	A->dice[5] = A->dice[3], A->dice[3] = A->dice[2], A->dice[2] = t;
}
void clockwise(DICE *A) {
	static int t;
	t = A->dice[2], A->dice[2] = A->dice[4];
	A->dice[4] = A->dice[5], A->dice[5] = A->dice[1], A->dice[1] = t;
}
DICE Data[1000000];
int cmp(const void *a, const void *b) {
	static DICE *i, *j;
	static int k;
	i = (DICE *)a, j = (DICE *)b;
	for(k = 0; k < 6; k++)
		if(i->dice[k] != j->dice[k])
			return i->dice[k] - j->dice[k];
	return 0;
}
void Print(DICE A) {
	static int i;
	for(i = 0; i < 6; i++)
		printf("%d ", A.dice[i]);
	puts("");
}
void Spin_dice(DICE A, int store) {
	static int i, j;
	for(i = 0; i < 6; i++)
		Data[store].dice[i] = A.dice[i];
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(cmp(&Data[store], &A) > 0)
				Data[store] = A;
			clockwise(&A);
		}		
		Right_turn(&A);
	}
	Up_turn(&A);
	for(i = 0; i < 2; i++) {
		for(j = 0; j < 4; j++) {
			if(cmp(&Data[store], &A) > 0)
				Data[store] = A;
			clockwise(&A);
		}		
		Up_turn(&A), Up_turn(&A);
	}
}
main() {
	int n, i, j;
	DICE A;
	A.dice[0] = 5, A.dice[1] = 2, A.dice[2] = 9;
	A.dice[3] = 1, A.dice[4] = 8, A.dice[5] = 4;
	Spin_dice(A, 0);
	while(scanf("%d", &n) == 1) {
		for(i = 0; i < n; i++) {
			for(j = 0; j < 6; j++)
				scanf("%d", &A.dice[j]);
			Spin_dice(A, i);
		}
		
		int Ans = 1;
		qsort(Data, n, sizeof(DICE), cmp);
		for(i = 1; i < n; i++) {
			if(cmp(&Data[i], &Data[i-1]))
				Ans++;
		}
		printf("%d\n", Ans);
	}
	return 0;
}
