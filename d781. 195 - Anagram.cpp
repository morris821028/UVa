#include<stdio.h>
int time[52] = {}, N;
char s[100];
void DFS(int now) {		
	int a;
	if(now == N) {
		s[now] = '\0';
		puts(s);
		return;
	}
	for(a = 0; a < 52; a++) 
		if(time[a] > 0) {
			time[a]--, s[now] = a&1 ? (a/2+'a') : (a/2+'A');
			DFS(now+1);
			time[a]++;
		}
}
main() {
	int t, a;
	char s[1000];
	scanf("%d", &t);
	while(t--) {
		scanf("%s", s);
		for(a = 0; a < 52; a++)	time[a] = 0;
		for(a = 0; s[a]; a++) {
			if(s[a] >= 'a')	time[(s[a]-'a')*2+1]++;
			else time[(s[a]-'A')*2]++;
		}
		N = a, DFS(0);
	}
	return 0;
}
