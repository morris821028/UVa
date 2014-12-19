#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define MAXN 128

int visited[3][3][MAXN];
int SG[3][3][MAXN]; // [start_elem][end_elem][n] => elem: NULL, X, O
int dfsSG(int st, int ed, int n) {
	if (visited[st][ed][n])	return SG[st][ed][n];
	if (n == 0)				return SG[st][ed][n] = 0;
	int &ret = SG[st][ed][n];
	visited[st][ed][n] = 1;
	map<int, int> mex;
	
	for (int i = 1; i <= n; i++) {
		for (int p = 1; p <= 2; p++) {
			if (i == 1 && st == p)	continue; // conflict XX or OO 
			if (i == n && ed == p)	continue; // conflict XX or OO 
			int nim = dfsSG(st, p, i - 1) ^ dfsSG(p, ed, n - i);
			mex[nim] = 1;
		}
	}
	
	int last = -1;
	for (map<int, int>::iterator it = mex.begin();
		it != mex.end(); it++) {
		if (it->first > last + 1)
			return ret = (last + 1);
		last = it->first;
	}
	return ret = (last + 1);
}
int main() {
	int testcase;
	char s[128];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int st, ed, n = strlen(s);
		int ret = 0, round = 0, tmp = 0;
		
		st = ed = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '.')
				tmp++;
			if (s[i] == 'O' || s[i] == 'X') {
				ed = s[i] == 'O' ? 1 : 2;
				ret = ret ^ dfsSG(st, ed, tmp);
				st = ed, tmp = 0;
				round++;
			}
		}
		ret = ret ^ dfsSG(st, 0, tmp);
		ret = round%2 ? !ret : ret; 
		puts(ret ? "Possible." : "Impossible.");
	}
	return 0;
}
/*
3
...
X..
O
*/
