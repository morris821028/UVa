#include <stdio.h>

struct Matrix {
	int cnt;
	int one[100];
};

typedef struct Matrix Matrix;

int N, M;
Matrix matrix[1000];

void search(int, int, int*, int, int[]);

int main() {
	int i, j, min;
	int set[1001];
	freopen("in1.txt", "rt", stdin);   
	freopen("out1.txt", "w+t", stdout);
	while(scanf("%d %d", &N, &M) == 2) {
		for(i = 0; i < N; i++) {
			scanf("%d", &matrix[i].cnt);
			
			for(j = 0; j < matrix[i].cnt; j++)
				scanf("%d", &matrix[i].one[j]);
		}
		
		min = 2147483647;
		memset(set, 0, sizeof(set));
		for(i = 0; i < N; i++)
			search(i, 0, &min, 0, set);
		
		printf("%d\n", min);
	}
	
	return 0;
}

void search(int index, int cnt, int *min, int setCnt, int set[]) {
	int i;
	
	if(setCnt == M) {
		*min = cnt < *min?cnt:*min;
		return ;
	}
	
	if(matrix[index].cnt+setCnt > M)
		return ;
	
	for(i = 0; i < matrix[index].cnt; i++)
		if(set[matrix[index].one[i]] == 1)
			return ;
	
	for(i = 0; i < matrix[index].cnt; i++)
		set[matrix[index].one[i]] = 1;
	
	for(i = 0; i < N; i++)
		if(i != index)
			search(i, cnt+1, min, setCnt+matrix[index].cnt, set);
	
	for(i = 0; i < matrix[index].cnt; i++)
		set[matrix[index].one[i]] = 0;
}

