#include <bits/stdc++.h>
using namespace std;

int readDir() {
	char s[16];
	scanf("%s", s);
	int ret = 0;
	if (s[1] == 'x')
		ret = 1;
	else if (s[1] == 'y')
		ret = 2;
	else
		ret = 3;
	if (s[0] == '-')
		ret = -ret;
	return ret;
}

namespace {
	int X, Y, Z;
	int IX, IY, IZ, ID;
	int OX, OY, OZ, OD;
	int TX, TY, TZ;
	int ret;
	const int MAXN = 22;
	int used[MAXN][MAXN][MAXN];
	
	int test_place(int x, int y, int z, int d1, int s1, int d2, int s2)	{
		if (abs(d1) == abs(d2))
			return 0;
		int valid = 1;
		int tx = x, ty = y, tz = z;
		int d1x = abs(d1) == 1 ? (d1 < 0 ? -1 : 1) : 0;
		int d1y = abs(d1) == 2 ? (d1 < 0 ? -1 : 1) : 0;
		int d1z = abs(d1) == 3 ? (d1 < 0 ? -1 : 1) : 0;
		int d2x = abs(d2) == 1 ? (d2 < 0 ? -1 : 1) : 0;
		int d2y = abs(d2) == 2 ? (d2 < 0 ? -1 : 1) : 0;
		int d2z = abs(d2) == 3 ? (d2 < 0 ? -1 : 1) : 0;
		for (int it = 0; it < s1 && valid; it++) {
			if (tx < 1 || ty < 1 || tz < 1 ||
				tx > X || ty > Y || tz > Z || used[tx][ty][tz]) {
				valid = 0;
				continue;
			}
			if (it != s1-1)
				tx += d1x, ty += d1y, tz += d1z;
			else
				tx += d2x, ty += d2y, tz += d2z;
		}
		for (int it = 0; it < s2 && valid; it++) {
			if (tx < 1 || ty < 1 || tz < 1 ||
				tx > X || ty > Y || tz > Z || used[tx][ty][tz]) {
				valid = 0;
				continue;
			}
			tx += d2x, ty += d2y, tz += d2z;
		}
		return valid;
	}
	void place(int x, int y, int z, int d1, int s1, int d2, int s2, 
				int &tx, int &ty, int &tz)	{
		tx = x, ty = y, tz = z;
		int d1x = abs(d1) == 1 ? (d1 < 0 ? -1 : 1) : 0;
		int d1y = abs(d1) == 2 ? (d1 < 0 ? -1 : 1) : 0;
		int d1z = abs(d1) == 3 ? (d1 < 0 ? -1 : 1) : 0;
		int d2x = abs(d2) == 1 ? (d2 < 0 ? -1 : 1) : 0;
		int d2y = abs(d2) == 2 ? (d2 < 0 ? -1 : 1) : 0;
		int d2z = abs(d2) == 3 ? (d2 < 0 ? -1 : 1) : 0;
		for (int it = 0; it < s1; it++) {
			used[tx][ty][tz] = 1;
			if (it != s1-1)
				tx += d1x, ty += d1y, tz += d1z;
			else
				tx += d2x, ty += d2y, tz += d2z;
		}
		for (int it = 0; it < s2; it++) {
			used[tx][ty][tz] = 1;
			tx += d2x, ty += d2y, tz += d2z;
		}
	}
	void cancel(int x, int y, int z, int d1, int s1, int d2, int s2)	{
		int tx = x, ty = y, tz = z;
		int d1x = abs(d1) == 1 ? (d1 < 0 ? -1 : 1) : 0;
		int d1y = abs(d1) == 2 ? (d1 < 0 ? -1 : 1) : 0;
		int d1z = abs(d1) == 3 ? (d1 < 0 ? -1 : 1) : 0;
		int d2x = abs(d2) == 1 ? (d2 < 0 ? -1 : 1) : 0;
		int d2y = abs(d2) == 2 ? (d2 < 0 ? -1 : 1) : 0;
		int d2z = abs(d2) == 3 ? (d2 < 0 ? -1 : 1) : 0;
		for (int it = 0; it < s1; it++) {
			used[tx][ty][tz] = 0;
			if (it != s1-1)
				tx += d1x, ty += d1y, tz += d1z;
			else
				tx += d2x, ty += d2y, tz += d2z;
		}
		for (int it = 0; it < s2; it++) {
			used[tx][ty][tz] = 0;
			tx += d2x, ty += d2y, tz += d2z;
		}
	}
	void debug() {
		for (int i = 1; i <= Z; i++) {
			for (int j = Y; j >= 1; j--) {
				for (int k = 1; k <= X; k++)
					printf("%c", used[k][j][i] ? '#' : '.');
				puts("");
			}
			puts("");
		}
	}
	void dfs(int x, int y, int z, int d, int step) {
		if (step >= ret || step >= 7)
			return ;
		if (x == TX && y == TY && z == TZ) {
			if (d == OD)
				ret = min(ret, step);
			return ;
		}
//		getchar();
//		fprintf(stderr, "ff %d %d %d %d\n", x, y, z, d);
//		debug();
		
		for (int i = 2; i <= 3; i++) {
			for (int dir = 1; dir <= 3; dir++) {
				if (test_place(x, y, z, d, i, dir, 4-i)) {
					int tx, ty, tz;
					place(x, y, z, d, i, dir, 4-i, tx, ty, tz);
					dfs(tx, ty, tz, dir, step+1);
					cancel(x, y, z, d, i, dir, 4-i);
				}
				if (test_place(x, y, z, d, i, -dir, 4-i)) {
					int tx, ty, tz;
					place(x, y, z, d, i, -dir, 4-i, tx, ty, tz);
					dfs(tx, ty, tz, -dir, step+1);
					cancel(x, y, z, d, i, -dir, 4-i);
				}
			}	
		}
	}
	int search() {
		ret = 0x3f3f3f3f;
		memset(used, 0, sizeof(used));
		TX = OX, TY = OY, TZ = OZ; 
		if (OD == -1)		TX--;
		else if (OD == 1)	TX++;
		else if (OD == -2)	TY--;
		else if (OD == 2)	TY++;
		else if (OD == -3)	TZ--;
		else if (OD == 3)	TZ++;
		dfs(IX, IY, IZ, ID, 0);
		return ret == 0x3f3f3f3f ? -1 : ret;
	}
}
int main() {
	int cases = 0;
	while (scanf("%d %d %d", &X, &Y, &Z) == 3 && X) {
		scanf("%d %d %d", &IX, &IY, &IZ);
		ID = readDir();
		scanf("%d %d %d", &OX, &OY, &OZ);
		OD = readDir();
		
		printf("Case %d: ", ++cases);
		int ret = search();
		if (ret >= 0)
			printf("%d\n", ret);
		else
			puts("Impossible");
	}
	return 0;
}
/*
5  4  3  3  1  1  +z  5  4  3  +x
5  4  3  3  1  1  +z  1  2  3  -x
*/
