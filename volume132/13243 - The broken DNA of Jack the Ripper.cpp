#include <bits/stdc++.h>
using namespace std;

inline int toIndex(char c) {
	switch(c) {
		case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
		case '-': return 4;
	}
	assert(false);
}

const int MAXN = 20005;
const int MAXS = 105;
uint32_t bit[MAXN][4][4];
uint32_t mask[MAXN][4];

void store(char s[], int i, int m) {
	for (int j = 0; j < m; j++) {
		int c = toIndex(s[j]);
		if (c == 4) {
			mask[i][j>>5] |= 1U<<(j&31);
		} else {
			bit[i][c][j>>5] |= 1U<<(j&31);
		}
	}
}
int main() {
	int n;
	char s[105];
	while (scanf("%d", &n) == 1) {
		memset(bit, 0, sizeof(bit));
		memset(mask, 0, sizeof(mask));
		scanf("%s", s);
		int m = strlen(s);
		int b = (m>>5) + ((m&31) != 0);
		store(s, 0, m);
		for (int i = 1; i < n; i++) {
			scanf("%s", s);
			store(s, i, m);

			vector<int> ret;
			for (int j = 0; j < i; j++) {
				int ok = 1;
				for (int c = 0; c < 4; c++) {
					for (int k = 0; k < b; k++) {
						uint32_t diff = bit[i][c][k]^bit[j][c][k];
						if (diff && (diff&(mask[i][k]|mask[j][k]) != diff) {
							ok = 0;
							goto DONE;
						}
					}
				}
				DONE:
				if (ok)
					ret.push_back(j);
			}
			if (ret.size()) {
				printf("%d:", i+1);
				for (auto e : ret)
					printf(" %d", e+1);
				puts("");
			}
		}
	}
	return 0;
}
/*
8
AC-CG-
A-A-GG
ACACGT
ACACGG
ACACAC
---TT-
------
ACACAC
*/
