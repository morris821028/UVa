#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;
int inL[128] = {}, N, Q, Llen;
char L[128], s[1024];
char text[128];
int sol;
void dfs(int idx, int pl, int m) {
	while (s[idx] == ' ')	text[pl++] = ' ', idx++;
	if (sol >= 2)	return;
	if (s[idx] == '\0') {
		sol++;
		text[pl] = '\0';
		puts(text);
		return;
	}
	
	char a, b, c;
	for (int i = 'A'; i <= 'Z'; i++) {
		if (inL[i]) {
			a = L[m%Llen];
			b = (i-'A'+N)%26 + 'A';
			c = L[(m+1)%Llen];
			text[pl] = i;
			if (a == s[idx] && b == s[idx+1] && c == s[idx+2]) {
				dfs(idx+3, pl+1, m+1);
			}
		} else {
			a = (i-'A'+N)%26 + 'A';
			text[pl] = i;
			if (a == s[idx]) {
				dfs(idx+1, pl+1, m);
			}
		} 
	}
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", L);
		scanf("%d %d", &N, &Q);
		memset(inL, 0, sizeof(inL));
		for (int i = 0; L[i]; i++)
			inL[L[i]] = 1;
		Llen = strlen(L);
		while (getchar() != '\n');
		for (int i = 0; i < Q; i++) {
			gets(s);
			sol = 0;
			dfs(0, 0, 0);
			if (sol != 1)
				puts("error in encryption");
		}
		if (testcase)
			puts("");
	}
	return 0;
}
