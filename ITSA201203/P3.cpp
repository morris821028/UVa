#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
char S[10][10], P[10][2];
int n, flag;
int choose[5], pp[1];
void DFS(int now, int last) {
	int i, j, k;
	if(flag == 1)	return;
	if(now == 3) {
		//printf("%c%c%c\n", choose[0], choose[1], choose[2]);
		int ASCII[256] = {}, count = 0;
		ASCII[choose[0]] = 1;
		ASCII[choose[1]] = 1;
		ASCII[choose[2]] = 1;
		for(i = 'I'; i <= 'P'; i++) {
			count = 0;
			for(j = 0; j < n; j++) {
				if(i != P[j][0])
					continue;
				int tmp = 0;
				for(k = 0; k < 5; k++)
					if(ASCII[S[j][k]] == 1)
						tmp++;
				if(tmp == 3)	count++;
			}
			if(count >= n/2+n%2) {
				flag = 1;
				for(j = 0; j < 3; j++)
					printf("%c", choose[j]);
				printf("%c\n", i);
				return;
			}
		}
		return;
	}
	for(i = last; i <= 'H'; i++) {
		choose[now] = i;
		DFS(now+1, i+1);
	}
}
int main() {
	int t, i;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%s %s", S[i], P[i]);
		}
		flag = 0;
		DFS(0, 'A');
		if(flag == 0)
			puts("No answer");
	}
    return 0;
}
/*
2
5
BCDEF N
DEFGH N
ABCDE M
BCDEF N
CDEFG N
*/
