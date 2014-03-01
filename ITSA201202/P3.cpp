#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int way[10][20][10] = {
		{},
		{{1,-1}},
		{{4,-1},{0,1,-1}},
		{{5,1,-1},{0,0,1,-1},{9,-1}},
		{{16,-1},{0,4,-1},{0,0,0,1,-1},{7,0,1,-1},{4,3,-1},{8,2,-1},{12,1,-1}},
		{{25,-1},{13,3,-1},{4,3,1,-1},{9,0,0,0,1,-1},{0,0,0,0,1,-1},{17,2,-1},{21,1,-1},{4,3,1,-1},{8,2,1,-1},{12,1,1,-1},{16,0,1,-1},{9,0,0,1,-1},{16,0,1,-1},{9,4,-1}}
};
int wt[10] = {
	0,
	1,
	2,
	3,
	7,
	14,
};
int count[6], flag, one;
void DFS(int);
void C(int now) {
	int i, j;
	for(i = 0; i < wt[one]; i++) {
		for(j = 0; way[one][i][j] != -1; j++) {
			if(count[j] < way[one][i][j])
				break;
		}
		if(way[one][i][j] == -1) {
			
			for(j = 0; way[one][i][j] != -1; j++) {
					count[j] -= way[one][i][j];
			}
			DFS(now+1);
			for(j = 0; way[one][i][j] != -1; j++) {
					count[j] += way[one][i][j];
			}
		}
	}
}
void DFS(int now) {
	if(now == 6) {
		flag = 1;
		return;
	} 
	if(flag == 1)	return;
	
	C(now);
}
int main() {
	int n, N, i, x;
	while(scanf("%d", &n) == 1)
	while(n--) {
		scanf("%d", &N);
		memset(count, 0, sizeof(count));
		int sum = 0;
		for(i = 0; i < N; i++) {
			scanf("%d", &x);
			if(x == 1)	count[0]++;
			if(x == 4)	count[1]++;
			if(x == 9)	count[2]++;
			if(x == 16)	count[3]++;
			if(x == 25)	count[4]++;
			sum += x;
		}
		one = sum/6;
		int tmp = sqrt(one);
		if(sum%6!= 0 || tmp > 5 || one != tmp*tmp)	puts("no");
		else {
			flag = 0;
			one = tmp;
			DFS(0);
			if(flag)	puts("yes");
			else		puts("no");
		}
	}
    return 0;
}
/*
5
6 4 4 4 4 4 4
11 4 9 1 1 16 9 1 1 1 4 9
13 16 9 9 4 16 4 4 1 1 9 4 1 4
22 4 1 16 9 4 4 1 1 1 4 16 1 4 1 1 16 1 4 1 4 1 1
9 4 1 4 1 1 4 1 4 4
*/
