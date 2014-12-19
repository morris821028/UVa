#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define MAXN 256

int visited[MAXN];
int SG[MAXN]; // [start_elem][end_elem][n] => elem: NULL, X, O
int dfsSG(int n) {
	if (visited[n])	return SG[n];
	if (n == 0)		return SG[n] = 0;
	int &ret = SG[n];
	visited[n] = 1;
	map<int, int> mex;
	
	for (int i = 1; i <= n; i++) {
		int nim = dfsSG(max(i - 3, 0)) ^ dfsSG(max(n - i - 2, 0));
		mex[nim] = 1;
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

int isCompleted(char s[]) {
	for (int i = 0; s[i]; i++) {
		if (s[i] == 'X' && s[i+1] == 'X' && s[i+2] == 'X')
			return 1;
	}
	return 0;
}

int testGame(char s[], int n) {
	for (int i = 0; i < n; i++) {
		if (s[i] == '.') {
			s[i] = 'X';
			if (isCompleted(s)) {
				s[i] = '.';
				return 0;
			}
			s[i] = '.';
		}
	}
	int ret = 0, tmp = 0;
	for (int i = 0; i < n; i++) {
		int split = 0;
		for (int j = -2; j <= 2; j++) {
			int x = i + j;
			if (x >= 0 && x < n && s[x] == 'X')
				split = 1;
		}
		if (split) {
			ret ^= dfsSG(tmp), tmp = 0;
		} else {
			tmp++;
		}
	}
	ret ^= dfsSG(tmp);
	return ret == 0;
}
int main() {
	char s[MAXN];
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		
		vector<int> winPos;
		int n = strlen(s);
		for (int i = 0; i < n; i++) {
			if (s[i] == '.') {
				s[i] = 'X';
				if (isCompleted(s) || testGame(s, n))
					winPos.push_back(i);
				s[i] = '.';
			}
		}
		
		if (winPos.size()) {
			puts("WINNING");
			for (int i = 0; i < winPos.size(); i++)
				printf("%d%c", winPos[i] + 1, i == winPos.size() - 1 ? '\n' : ' ');
		} else {
			puts("LOSING\n");
		}
	}
	return 0;
}
/*
4
.....
X.....X..X.............X....X..X
.X.X...X
...............................................
*/
