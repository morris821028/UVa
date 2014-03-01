#include<stdio.h>
#include<string.h>
int Map[26][26], App[26], Used[26];
void compare(const char *A, const char *B) {
	while(*A && *B && *A == *B) {
		A++;
		B++;
	}
	if(*A && *B) {
		char cA, cB;
		cA = *A - 'A', cB = *B - 'A';
		Map[cA][cB] = 1;
		App[cA] = 1, App[cB] = 1;
	}
}
int main() {
	int n = 0, i, j;
	char *pre = new char[255];
	char *cur = new char[255];
	memset(Map, 0, sizeof(Map));
	memset(App, 0, sizeof(App));
	memset(Used, 0, sizeof(Used));
	
	scanf("%s", pre), n++;
	while(scanf("%s", cur) == 1) {
		if(cur[0] == '#')	break;
		compare(pre, cur);
		char *tmp;
		tmp = pre, pre = cur, cur = tmp;
		n++;
	}
	while(1) {
		for(i = 0; i < 26; i++) {
			for(j = 0; j < 26; j++)
				if(Map[j][i])
					break;
			if(j == 26 && App[i])	break;
		}
		if(i == 26) break;
		App[i] = 0;
		for(j = 0; j < 26; j++)	Map[i][j] = 0;
		printf("%c", i+'A');
	}
	if(n == 1) printf("%c", pre[0]);
	puts("");
    return 0;
}
