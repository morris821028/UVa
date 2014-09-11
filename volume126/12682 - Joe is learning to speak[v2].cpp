#include <stdio.h>
#include <set>
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <functional>
using namespace std;
set<int> mem[6];
int N;
int isSeparate(char c) {
	static string separate = ".,:;?!";
	return separate.find(c) != string::npos;
}
int hash(const char s[], int value) {
	int a = 63689, b = 378551;
	for (int i = 0; s[i]; i++)
		value = value * a + s[i], a *= b;
	return value;
}
void memorize(int n, char stmt[][32]) {
	for (int j = 1; j <= N; j++) {
		for (int k = 0; k + j - 1 < n; k++) {
			int value = 0;
			for (int p = 0; p < j; p++) {
				if (p)	value = hash("*", value);
				value = hash(stmt[k+p], value);
			}
			mem[j].insert(value);
		}
	}
}
int check(int n, char stmt[][32]) {
	for (int j = 1; j <= N; j++) {
		for (int k = 0; k + j - 1 < n; k++) {
			int value = 0;
			for (int p = 0; p < j; p++) {
				if (p)	value = hash("*", value);
				value = hash(stmt[k+p], value);
			}
			if (mem[j].find(value) == mem[j].end())
				return 1;
		}
	}
	return 0;
}
void build() {
	for (int i = 1; i <= N; i++)
		mem[i].clear();
	mem[1].insert(hash("joe", 0));
	char stmt[128][32];
	for (int i = 0; ; i++) {
		int end = 0, n = 0;
		while (scanf("%s", stmt[n]) == 1) {
			if (isSeparate(stmt[n][0]))
				break;
			if (stmt[n][0] == '*') {
				end = 1;
				break;
			}
			n++;
		}
		if (end)	break;
		for (int j = 0; j < n; j++) {
			for (int k = 0; stmt[j][k]; k++)
				stmt[j][k] = tolower(stmt[j][k]);
		}
		memorize(n, stmt);
	}
}
void query() {
	char stmt[128][32], stmt2[128][32];
	int end = 0;
	for (int i = 0; !end; i++) {
		int n = 0;
		while (scanf("%s", stmt[n]) == 1) {
			if (isSeparate(stmt[n][0]))
				break;
			if (stmt[n][0] == '#') {
				end = 1;
				break;
			}
			n++;
		}
		for (int j = 0; j < n; j++) {
			strcpy(stmt2[j], stmt[j]);
			for (int k = 0; stmt[j][k]; k++)
				stmt2[j][k] = tolower(stmt2[j][k]);
		}
		for (int j = 0; j < n; j++)  {
			if(mem[1].find(hash(stmt2[j], 0)) == mem[1].end()) {
				printf("What does the word \"%s\" mean?\n", stmt[j]);
				mem[1].insert(hash(stmt2[j], 0));
			}
		}
		if (check(n, stmt2)) {
			printf("What does the sentence \"");
			for (int j = 0; j < n; j++) {
				printf("%s%c", stmt[j], j == n-1 ? '"' : ' ');
			}
			puts(" mean?");
			memorize(n, stmt2);
		}
	}
}
int main() {
	int cases = 0;
	while(scanf("%d", &N) == 1) {
		if (cases++)	puts("");
		build();
		printf("Learning case %d\n", cases);
		query();
	}
	return 0;
}
/*
2
hello sam . say hello to everybody . good bye .
*
say hi to everybody .
hi to everybody .
hello joe .
swerc
#
4
Joe is my name . I have a dog . My dog is
a
cinnamon coloured golden retriever
. The name of my father is Ben and the name
of my mother is Linda .
*
Hello Joe , how are you ? Are you my friend ?
Last day you told me : the name of my mother is Linda .
You also told me : the name of my father is Ben .
How are you my friend ?
#
*/
