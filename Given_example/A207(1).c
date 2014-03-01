#include <stdio.h>
#include <time.h>
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

int N, M, setCnt;
int set[1001];
Matrix matrix[1001];
Pile pile[1001];

void search(int, int, int*);

int main() {
	int i, j, min, flag;
	clock_t st, ed;
	
	st = clock();
	while(scanf("%d %d", &N, &M) == 2) {
		for(i = 0; i <= 1000; i++)
			matrix[i].cnt = pile[i].cnt;
		
		memset(set, 0, sizeof(set));
		for(i = 0; i < N; i++) {
			scanf("%d", &matrix[i].cnt);
			
			for(j = 0; j < matrix[i].cnt; j++)
				scanf("%d", &matrix[i].one[j]), set[matrix[i].one[j]] = 1;
			pile[matrix[i].one[0]].repeat[pile[matrix[i].one[0]].cnt++] = i;
		}
		
		flag = 0;
		for(i = 1; i <= M&&flag == 0; i++)
			if(set[i] == 0)
				flag = 1;
		
		if(flag == 0) {
			min = MAX;
			setCnt = 0;
			memset(set, 0, sizeof(set));
			search(1, 0, &min);
			
			printf(min == MAX?"No\n":"%d\n", min);
		} else
			puts("No");
	}
	ed = clock();
	printf("[%f]\n", (float)(ed - st )/CLOCKS_PER_SEC);
	
	return 0;
}

void search(int k, int cnt, int *min) {
	int i, j, t, flag;
	
	if(cnt > *min)
		return ;
	
	if(setCnt == M) {
		*min = cnt < *min?cnt:*min;
		return ;
	}
	
	if(k > M)
		return ;
	
	if(set[k] == 1) {
		search(k+1, cnt, min);
		return ;
	}
	
	for(i = 0; i < pile[k].cnt; i++) {
		if(matrix[pile[k].repeat[i]].cnt+setCnt > M)
			continue;
		
		flag = 0;
		for(j = 0; j < matrix[pile[k].repeat[i]].cnt&&flag == 0; j++)
			if(set[matrix[pile[k].repeat[i]].one[j]] == 1)
				flag = 1;
		
		if(flag == 1)
			continue;
		
		for(j = 0; j < matrix[pile[k].repeat[i]].cnt; j++)
			set[matrix[pile[k].repeat[i]].one[j]] = 1;
		setCnt += matrix[pile[k].repeat[i]].cnt;
		
		search(k+1, cnt+1, min);
		
		for(j = 0; j < matrix[pile[k].repeat[i]].cnt; j++)
			set[matrix[pile[k].repeat[i]].one[j]] = 0;
		setCnt -= matrix[pile[k].repeat[i]].cnt;
	}
	
}

