#include <stdio.h>
#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
set<string> mem[6];
int N;
int isSeparate(char c) {
	static string separate = ".,:;?!";
	return separate.find(c) != string::npos;
}
void memorize(int n, string stmt[]) {
	for (int j = 1; j <= N; j++) {
		for (int k = 0; k + j - 1 < n; k++) {
			string mm = "";
			for (int p = 0; p < j; p++) {
				if (p)	mm += "*";
				mm += stmt[k+p];
			}
			mem[j].insert(mm);
		}
	}
}
int check(int n, string stmt[]) {
	for (int j = 1; j <= N; j++) {
		for (int k = 0; k + j - 1 < n; k++) {
			string mm = "";
			for (int p = 0; p < j; p++) {
				if (p)	mm += "*";
				mm += stmt[k+p];
			}
			if (mem[j].find(mm) == mem[j].end())
				return 1;
		}
	}
	return 0;
}
void build() {
	for (int i = 1; i <= N; i++)
		mem[i].clear();
	mem[1].insert("joe");
	string stmt[128];
	char s[32];
	for (int i = 0; ; i++) {
		int end = 0, n = 0;
		while (scanf("%s", s) == 1) {
			if (isSeparate(s[0]))
				break;
			if (s[0] == '*') {
				end = 1;
				break;
			}
			stmt[n++] = s;
		}
		if (end)	break;
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < stmt[j].length(); k++)
				stmt[j][k] = tolower(stmt[j][k]);
		}
		memorize(n, stmt);
	}
}
void query() {
	string stmt[128], stmt2[128];
	int end = 0;
	char s[32];
	for (int i = 0; !end; i++) {
		int n = 0;
		while (scanf("%s", s) == 1) {
			if (isSeparate(s[0]))
				break;
			if (s[0] == '#') {
				end = 1;
				break;
			}
			stmt[n++] = s;
		}
		for (int j = 0; j < n; j++) {
			stmt2[j] = stmt[j];
			for (int k = 0; k < stmt[j].length(); k++)
				stmt2[j][k] = tolower(stmt2[j][k]);
		}
		for (int j = 0; j < n; j++)  {
			if(mem[1].find(stmt2[j]) == mem[1].end()) {
				printf("What does the word \"%s\" mean?\n", stmt[j].c_str());
				mem[1].insert(stmt2[j]);
			}
		}
		if (check(n, stmt2)) {
			printf("What does the sentence \"");
			for (int j = 0; j < n; j++) {
				printf("%s%c", stmt[j].c_str(), j == n-1 ? '"' : ' ');
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
