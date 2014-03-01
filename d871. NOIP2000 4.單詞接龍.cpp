#include<stdio.h>
#include<string.h>
char idiom[20][300];
int Map[20][20], Used[20], l[20], Max, n;
void Build(int n) {
	int a, b, c, d, k; 
	Max = 0; 
	for(a = 0; a < n; a++) { 
		for(b = 0; b < n; b++) 
			Map[a][b] = 0; 
		l[a] = strlen(idiom[a]); 
		Used[a] = 0; 
	} 
	for(a = 0; a < n; a++) 
		for(b = 0; b < n; b++) {
			for(k = 1; k <= l[a]; k++) {
				for(c = 0, d = l[a]-k; c < k; c++, d++) 
					if(idiom[a][d] != idiom[b][c])
						break;
				if(c == k) break; 
			} 
			if(k <= l[a])
				Map[a][b] = l[b] - k;
		}
} 
void DFS(int now, int sum) {
	int a;
	if(sum > Max) Max = sum;
	for(a = 0; a < n; a++) 
		if(Map[now][a] > 0 && Used[a] < 2) {
			Used[a]++;
			DFS(a, sum+Map[now][a]); 
			Used[a]--; 
		} 
} 
main() {
	int a;
	char st[2]; 
	while(scanf("%d", &n) == 1) {
		for(a = 0; a < n; a++) 
			scanf("%s", &idiom[a]); 
		scanf("%s", st); 
		Build(n); 
		for(a = 0; a < n; a++)
			if(idiom[a][0] == st[0]) {
				Used[a] = 1;
				DFS(a, l[a]); 
				Used[a] = 0; 
			} 
		printf("%d\n", Max); 
	}
	return 0; 
}
