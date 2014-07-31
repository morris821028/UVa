#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

void gaussianElimination(double mtx[][256], int n, double sol[], int nosol[]) {
#define eps 1e-6
    int i, j;		

    for(i = 0; i < n; i++) {
        int k = i;
        for(j = i; j < n; j++)
            if(fabs(mtx[k][i]) < fabs(mtx[j][i]))
                k = j;
        if(fabs(mtx[k][i]) < eps)
            continue;
        if(k != i) {
            for(j = 0; j <= n; j++)
                swap(mtx[k][j], mtx[i][j]);
        }
        for(j = 0; j < n; j++) {
            if(i == j)  continue;
            for(k = n; k >= i; k--) {
                mtx[j][k] -= mtx[j][i]/mtx[i][i]*mtx[i][k];
            }
        }
    }	
//	for(int i = 0; i < n; i++) {
//		for(int j = 0; j <= n; j++)
//			printf("%lf ", mtx[i][j]);
//		puts("");
//	}
    for(int i = 0; i < n; i++)
    	nosol[i] = 0;
    for(i = n-1; i >= 0; i--) {
        if(fabs(mtx[i][i]) < eps)
            nosol[i] = 1;
        else {
            if(fabs(mtx[i][n]) < eps)
                sol[i] = 0;
            else
                sol[i] = mtx[i][n]/mtx[i][i];
        }
        for(j = i+1; j < n; j++)
            if(fabs(mtx[i][j]) > eps && nosol[j])
                nosol[i] = 1;
    }
}

vector<int> depend[512];
int visited[512], in_stk[512];
int dfs(int u, int p) {
	visited[u] = 1, in_stk[u] = 1; 
	for(int i = 0; i < depend[u].size(); i++) {
		int v = depend[u][i];
		if(in_stk[v])	return 1;
		if(visited[v] == 0 && dfs(v, u))
			return 1;
	}
	in_stk[u] = 0;
	return 0;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int N, M;
	char s[1025], exp[32][32][128];
	while(scanf("%d %d", &N, &M) == 2 && N+M) {
		while(getchar() != '\n');
		
		int notsolvable[256];
		double f[256][256] = {}, value[256];
		
		for(int i = 0; i < N * M; i++) {
			depend[i].clear();
		}
		
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				scanf("%s", s);
				strcpy(exp[i][j], s);
				int sign = 1;
				f[i * M + j][i * M + j] = 1;
				for(int k = 0; s[k]; k++) {
					if(s[k] == '+')			sign = 1;
					else if(s[k] == '-')	sign = -1;
					else if('0' <= s[k] && s[k] <= '9') {
						int num = 0;
						while('0' <= s[k] && s[k] <= '9')
							num = num * 10 + s[k] - '0', k++;
						k--;
						f[i * M + j][N * M] += sign * num;
					} else {
						int rol = s[k] - 'A', num = 0;
						k++;
						while('0' <= s[k] && s[k] <= '9')
							num = num * 10 + s[k] - '0', k++;
						k--;
						f[i * M + j][rol * M + num] -= sign;
						depend[i * M + j].push_back(rol * M + num);
					}
				}
			}
		}
		gaussianElimination(f, N*M, value, notsolvable);
		for(int i = 0; i < N*M; i++) {
			memset(visited, 0, sizeof(visited));
			memset(in_stk, 0, sizeof(in_stk));
			notsolvable[i] |= dfs(i, i);
		}
		int allsol = 1;
		for(int i = 0; i < N*M; i++) {
//			printf("%lf %d\n", value[i], notsolvable[i]);
			allsol &= !notsolvable[i];
		}
		if(allsol) {
			printf(" ");
			for(int i = 0; i < M; i++)
				printf("%6d", i);
			puts("");
			for(int i = 0; i < N; i++) {
				printf("%c", i + 'A');
				for(int j = 0; j < M; j++)
					printf("%6d", (int)value[i * M +j]);
				puts("");
			}
		} else {
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < M; j++) {
					if(notsolvable[i * M + j]) {
						printf("%c%d: %s\n", i + 'A', j, exp[i][j]);
					}
				}
			}
		}
		puts("");
	} 
	return 0;
}
/*
2 2
A1+B1
5
3
B0-A1
3 2
A0
5
C1
7
A1+B1
B0+A1
0 0
*/
