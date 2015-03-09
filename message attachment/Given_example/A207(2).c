#include <stdio.h>
#define MAX 2147483647

struct Matrix {
	int cnt;
	int one[100];
};

struct Pile {
	int cnt;
	int repeat[1000];
};

typedef struct Matrix Matrix;
typedef struct Pile Pile;

int N, M;
Matrix matrix[1001];
Pile pile[1001];

void search(int, int, int*, int, int[]);

int main() {
	int i, j, min, flag;
	int set[1001];
	
	while(scanf("%d %d", &N, &M) == 2) {
		for(i = 0; i <= 1000; i++)
			matrix[i].cnt = pile[i].cnt = set[i] = 0;
		
		for(i = 0; i < N; i++) {
			scanf("%d", &matrix[i].cnt);
			
			for(j = 0; j < matrix[i].cnt; j++) {
				scanf("%d", &matrix[i].one[j]);
			}
			pile[matrix[i].one[0]].repeat[pile[matrix[i].one[0]].cnt++] = i;
		}
		
		flag = 1;
		for(i = 1; i <= M&&flag == 1; i++)
			if(pile[i].cnt == 0) flag = 0;
		
		if(flag == 1) {
			min = MAX;
			search(1, 0, &min, 0, set);
			
			printf(min == MAX?"No\n":"%d\n", min);
		} else
			puts("No");
		
	}
	
	return 0;
}

void search(int k, int cnt, int *min, int setCnt, int set[]) {
	int i, j, flag, flag2;
	if(set[setCnt]) {
		search(k+1, cnt, min, setCnt+1, set);
		return ;
	}
	if(setCnt == M) {
		*min = cnt < *min?cnt:*min;
		return ;
	}
	
	flag2 = 0;
	for(i = 0; i < pile[k].cnt; i++) {
		if(matrix[pile[k].repeat[i]].cnt+setCnt > M)
			continue;
		
		flag = 0;
		for(j = 0; j < matrix[pile[k].repeat[i]].cnt&&flag == 0; j++)
			if(set[matrix[pile[k].repeat[i]].one[j]] == 1)
				flag = 1;
		
		if(flag == 1)
			continue;
		flag2 = 1;
		
		for(j = 0; j < matrix[pile[k].repeat[i]].cnt; j++)
			set[matrix[pile[k].repeat[i]].one[j]] = 1;
		
		search(k+1, cnt+1, min, setCnt+matrix[pile[k].repeat[i]].cnt, set);
		
		for(j = 0; j < matrix[pile[k].repeat[i]].cnt; j++)
			set[matrix[pile[k].repeat[i]].one[j]] = 0;
	}
	
	if(flag2 == 0&&k < M)
		search(k+1, cnt, min, setCnt, set);
}

