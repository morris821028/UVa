#include <stdio.h>
#include <string.h>
char g[1<<21][2] = {};
int n, mask, highbit;
char order[2][1<<21], *p;
void dfs(int node) {
	int prefix = node;
	prefix <<= 1;
    for(int i = 0; i < 2; i++) {
        if(g[node][i]) {
            g[node][i]--;
            dfs((prefix|i)&mask);
    		*p = (i) +'0', p++;
        }
    }
}
int MinExp(const char *s, const int slen) {
    int i = 0, j = 1, k = 0, x, y, tmp;
    while(i < slen && j < slen && k < slen) {
        x = i + k;
        y = j + k;
        if(x >= slen)    x -= slen;
        if(y >= slen)    y -= slen;
        if(s[x] == s[y]) {
            k++;
        } else if(s[x] > s[y]) {
            i = j+1 > i+k+1 ? j+1 : i+k+1;
            k = 0;
            tmp = i, i = j, j = tmp;
        } else {
            j = i+1 > j+k+1 ? i+1 : j+k+1;
            k = 0;
        }
    }
    return i;
}
int main() {
	int testcase, K;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &K);
		mask = (1<<(n-1)) - 1;
		for(int i = (1<<(n-1)) - 1; i >= 0; i--) {
			g[i][0]++;
			g[i][1]++;
		}
		p = order[0];
		dfs(0);
		*p = '\0', p++;
		int len = strlen(order[0]);
		for(int i = len - 1, j = 0; i >= 0; i--, j++)
			order[1][i] = order[0][j];
		order[1][len] = '\0';
		int o1 = MinExp(order[0], len);
		int o2 = MinExp(order[1], len);
		int f = 0;
		for(int i = 0; i < len; i++) {
			if(order[0][(o1 + i)%len] != order[1][(o2 + i)%len]) {
				f = order[0][(o1 + i)%len] > order[1][(o2 + i)%len];
				break;
			}
		}
		int ret = 0;
		for(int i = 0; i < n; i++) {
			ret = ret << 1;
			if(f == 0) {
				ret |= order[0][(o1 + i + K)%len] - '0';
			} else {
				ret |= order[1][(o2 + i + K)%len] - '0';
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
