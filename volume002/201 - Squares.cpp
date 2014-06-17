#include<stdio.h>
#include<string.h>
int min(int x, int y) {
	return x < y ? x : y;
}
int main() {
	int n, m, flag = 0, x, y, i, j, k;
	char op[2];
	while(scanf("%d", &n) == 1) {
		if(flag)
			puts("\n**********************************\n");
		printf("Problem #%d\n\n", ++flag);
		scanf("%d", &m);
		int H[10][10], V[10][10], Ans[10],U, L;
		memset(H, 0, sizeof(H));
		memset(V, 0, sizeof(V));
		memset(Ans, 0, sizeof(Ans));
		while(m--) {
			scanf("%s %d %d", op, &x, &y);
			if(op[0] == 'H')	H[x][y] = 1;
			else				V[y][x] = 1;
		}
		for(i = n; i >= 0; i--)
			for(j = n; j >= 0; j--) {
				if(H[i][j]) H[i][j] = H[i][j+1]+1;
				if(V[i][j])	V[i][j] = V[i+1][j]+1;
			}
		for(i = 1; i <= n; i++)
			for(j = 1; j <= n; j++)
				for(k = min(H[i][j], V[i][j]); k >= 1; k--) {
					if(H[i+k][j] >= k && V[i][j+k] >= k)
						Ans[k]++;
				}
		int find = 0;
		for(i = 1; i < n; i++)
			if(Ans[i])
				printf("%d square (s) of size %d\n", Ans[i], i), find = 1;
		if(!find)
			puts("No completed squares can be found.");
	}
    return 0;
}
