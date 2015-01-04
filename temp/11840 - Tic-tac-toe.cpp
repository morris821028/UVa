#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define MAXN 10005
#define GET(x) (mex[x>>5]>>(x&31)&1)
#define SET(x) (mex[x>>5] |= 1<<(x&31))
int SG[MAXN], mex[(MAXN>>5) + 1];
int main() {
	SG[0] = 0;
	for (int i = 1; i < MAXN; i++) {
		memset(mex, 0, sizeof(mex));
		for (int j = 1; j <= i; j++) {
			int a = j - 3, b = j + 2;
			if (a < 0)	a = 0;
			if (b > i)	b = i;
			int nim = SG[a] ^ SG[i - b];
			SET(nim);
		}
		for (int j = 0; ; j++) {
			if (!GET(j)) {
				SG[i] = j;
				break;
			}
		}
	}
//	for (int i = 1; i <= 20; i++)
//		printf("%d %d\n", i, SG[i]);
	char s[10005];
	int n;
	const int dx[] = {-2, -1, 1, 2};
	while (scanf("%d", &n) == 1 && n) {
		scanf("%s", s);
		int place[MAXN] = {}, win = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == 'X') {
				place[i] = 1;
				for (int j = 0, k; j < 4; j++) {
					k = i + dx[j];
					if (k < 0 || k >= n)	continue;
					place[k] = 1;
				}
			}
			if (i+2 < n && s[i] == 'X' && s[i+2] == 'X')
				win = 1;
			if ((i+2 < n || i - 1 >= 0) && s[i] == 'X' && s[i+1] == 'X')
				win = 1;
		}
		if (win) {
			puts("S");
			continue;
		}
		int ret = 0, tmp = 0;
		for (int i = 0; i < n; i++) {
			if (place[i] == 0)
				tmp++;
			else {
				ret ^= SG[tmp], tmp = 0;
			}
		}
		ret ^= SG[tmp];
		puts(ret ? "S" : "N");
	}
	return 0;
}
/*
5
.....
5
..X..
6
X.X.X.
12
............
0
*/
