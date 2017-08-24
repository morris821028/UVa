#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 1024;
static int g[MAXN][MAXN], tmp[MAXN][MAXN];

static void copy(int n) {
	for (int i = 0; i < n; i++)
		memcpy(g[i], tmp[i], sizeof(g[0][0])*n);
}

static void rot(int n, int neg) {
	if (!neg) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				tmp[i][j] = g[n-j-1][i];
		}
	} else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				tmp[n-j-1][i] = g[i][j];
		}
	}
	copy(n);
}
static void sym(int n, int neg) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n/2; j++)
			swap(g[i][j], g[i][n-j-1]);
	}
}
static void bhsym(int n, int neg) {
	for (int i = n/2; i < n; i++) {
		for (int j = 0; j < n/2; j++)
			swap(g[i][j], g[i][n-j-1]);
	}
}
static void bvsym(int n, int neg) {
	for (int i = 0; i < n/2; i++) {
		for (int j = 0; j < n; j++)
			tmp[i][j] = g[i][j];
	}
	for (int i = n/2; i < n; i++) {
		for (int j = 0; j < n; j++)
			tmp[i][j] = g[3*n/2-1-i][j];
	}
	copy(n);
}
static void ddiv(int n, int neg) {
	if (!neg) {
		for (int i = 0; i < n; i++) {
			if (i&1) {
				for (int j = 0; j < n; j++)
					tmp[i/2+n/2][j] = g[i][j];
			} else {
				for (int j = 0; j < n; j++)
					tmp[i/2][j] = g[i][j];
			}
		}	
	} else {
		for (int i = 0; i < n; i++) {
			if (i&1) {
				for (int j = 0; j < n; j++)
					tmp[i][j] = g[i/2+n/2][j];
			} else {
				for (int j = 0; j < n; j++)
					tmp[i][j] = g[i/2][j];
			}
		}
	}
	copy(n);
}
static void mix(int n, int neg) {
	if (!neg) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if ((i&1) == 0) {
					if ((j&1) == 0)
						tmp[i][j] = g[i][j/2];
					else
						tmp[i][j] = g[i+1][j/2];
				} else {
					if ((j&1) == 0)
						tmp[i][j] = g[i-1][n/2+j/2];
					else
						tmp[i][j] = g[i][n/2+j/2];
				}
			}
		}
	} else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if ((i&1) == 0) {
					if ((j&1) == 0)
						tmp[i][j/2] = g[i][j];
					else
						tmp[i+1][j/2] = g[i][j];
				} else {
					if ((j&1) == 0)
						tmp[i-1][n/2+j/2] = g[i][j];
					else
						tmp[i][n/2+j/2] = g[i][j];
				}
			}
		}
	}
	copy(n);
}

void group(int n) { // Permutation group
	int ret = 1;
	static int used[MAXN][MAXN];
	memset(used, 0, sizeof(used));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (used[i][j])
				continue;
			int t, x, y, c = 0;
			used[i][j] = 1, c++;
			t = g[i][j];
			x = t/n, y = t%n;
			while (!used[x][y]) {
				used[x][y] = 1, c++;
				t = g[x][y];
				x = t/n, y = t%n;
			}
			if (c != 1) {
				int g = __gcd(c, ret);
				ret = ret/g*c;
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			assert(used[i][j] == 1);
	}
	printf("%d\n", ret);
}
void reverse(char s[]) {
	int n = strlen(s);
	for (int i = 0, j = n-1; i < j; i++, j--)
		swap(s[i], s[j]);
	for (int i = 0; i < n; i++) {
		if (s[i] > ' ') {
			int l = i, r = i;
			while (s[r] > ' ')
				r++;
			for (int p = l, q = r-1; p < q; p++, q--)
				swap(s[p], s[q]);
			i = r;
		}
	}
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g[i][j] = i*n + j;
		
		while (getchar() != '\n');
		
		static char line[65536], *cmd;
		fgets(line, 65536, stdin);
		reverse(line);
		cmd = strtok(line, " \n");
		while (cmd != NULL) {
			int len = strlen(cmd), neg = 0;
			if (cmd[len-1] == '-')
				cmd[len-1] = '\0', neg = 1;
			
			if (!strcmp(cmd, "rot"))
				rot(n, neg);
			else if (!strcmp(cmd, "sym"))
				sym(n, neg);		
			else if (!strcmp(cmd, "bhsym"))
				bhsym(n, neg);
			else if (!strcmp(cmd, "bvsym"))
				bvsym(n, neg);
			else if (!strcmp(cmd, "div"))
				ddiv(n, neg);
			else if (!strcmp(cmd, "mix"))
				mix(n, neg);
			cmd = strtok(NULL, " \n");
		}
		
		group(n);
		if (testcase)
			puts("");
	}
	return 0;
}
/*

4 

256
bvsym

256
bvsym div

256
div

1024
mix- div rot

-----

2

256
rot- div rot div

256
bvsym div mix
*/
