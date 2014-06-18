#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int A[1000], flag;
int	way[1000];
void DFS(int now, int goal,unsigned long long sum) {
	if(flag == 1)	return ;
	if(now >= goal) {
		if(sum == A[goal]) {
			int i;
			printf("%d", A[0]);
			for(i = 1; i < goal; i++) {
				if(way[i] == 0)
					printf("+");
				else if(way[i] == 1)
					printf("-");
				else if(way[i] == 2)
					printf("*");
				else if(way[i] == 3)
					printf("/");
				printf("%d", A[i]);
			}
			printf("=%d\n", A[goal]);
			flag = 1;
		}
		return;
	}
	way[now] = 0;
	DFS(now+1, goal, sum+A[now]);
	way[now] = 1;
	if(sum >= A[now])
		DFS(now+1, goal, sum-A[now]);
	way[now] = 2;
	DFS(now+1, goal, sum*A[now]);
	if(A[now] != 0 && sum%A[now] == 0) {
		way[now] = 3;
		DFS(now+1, goal, sum/A[now]);
	}
}
int main() {
	int m;
	char s[10000];
	scanf("%d", &m);
	getchar();
	while(m--) {
		gets(s);
		int tmp = 0, g = 0, i, idx = 0;
		for(i = 0; s[i]; i++) {
			if(s[i] >= '0' && s[i] <= '9') {
				tmp = tmp*10 + s[i]-'0', g = 1;
			} else {
				if(g == 1) {
					A[idx++] = tmp;
				}
				tmp = 0, g = 0;
			}
		}
		if(g == 1)	A[idx++] = tmp;	
		flag = 0;
		if(idx != 1)
			DFS(1, idx-1, A[0]);
		if(flag == 0)
			puts("No Solution");
	}
    return 0;
}
/*
1000
10000 9999 9998 9997 9996 9995 9994 9993 9992 9991
*/
