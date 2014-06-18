#include <stdio.h>
#define SIZE 1001

int main() {
	int i, j, n, m, a, flag;
	char graph[26][SIZE];
	char ans[55][SIZE];
	
	for(i = 0; i < SIZE; i++)
		ans[0][i] = ans[54][i] = '-';
	
	while(scanf("%d %d\n", &n, &m) == 2) {
		for(i = 0; i < m; i++)
			gets(graph[i]);
		
		for(i = 1; i <= 2*m+1; i++) {
			if(i%2 == 1) {
				ans[i][0] = 'A'+i/2;
				
				for(j = 1; j <= n; j++)
					ans[i][j] = '-';
				ans[i][j+1] = '\0';
			} else {
				ans[i][0] = ' ';
				
				for(j = 1; j <= n; j++)
					ans[i][j] = graph[i/2-1][j-1] == 'O'?'|':' ';
				ans[i][j+1] = '\0';
			}
		}
		
		flag = 0;
		for(i = 0; i <= m; i++) {
			a = i*2+1;
			for(j = 1; j <= n; j++) {
				if(ans[a-1][j] == '|')
					a -= 2;
				else if(ans[a+1][j] == '|')
					a += 2;
				
				if(ans[a-1][j] == '|'&&ans[a+1][j] == '|')
					flag = 1;
			}
			ans[a][j] = 'A'+i;
		}
		
		if(flag == 1)
			puts("ERROR");
		else
			for(i = 1; i <= 2*m+1; i++)
				puts(ans[i]);
		puts(" ");
	}
	
	return 0;
}

