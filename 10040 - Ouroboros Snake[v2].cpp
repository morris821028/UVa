#include <stdio.h>
#include <string.h>
#include <stack>
#include <algorithm>
using namespace std;
char g[1<<21][2] = {};
int n, mask;
char order[2][1<<21], *p;
char ouroboros[22][1<<21];
int olen[22];
void dfs(int node) {
	stack< pair<int, int> > stk;
	pair<int, int> state;
	int line;	
	stk.push(make_pair(node, 0));
	while(!stk.empty()) {
		state = stk.top(), stk.pop();
		node = state.first, line = state.second&3;
		if(line == 0) {
			int prefix = node << 1;
			if(g[node][0]) {
				g[node][0]--;
				stk.push(make_pair(node, 1|8));
				stk.push(make_pair((prefix|0)&mask, 0));
			} else {
				stk.push(make_pair(node, 1));
			}
		} else if(line == 1) {
			if(state.second&8) {
    			*p = (0) +'0', p++;
			}
			int prefix = node << 1;
			if(g[node][1]) {
				g[node][1]--;
				stk.push(make_pair(node, 2|8));
				stk.push(make_pair((prefix|1)&mask, 0));
			} else {
				stk.push(make_pair(node, 2));
			}
		} else {
			if(state.second&8) {
    			*p = (1) +'0', p++;
			}
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
void build() {
	for(int n = 1; n < 22; n++) {
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
		for(int i = 0; i < len; i++) {
			if(f == 0) {
				ouroboros[n][i] = order[0][(o1 + i)%len];
			} else {
				ouroboros[n][i] = order[1][(o2 + i)%len];
			}
		}
		olen[n] = len;
	}
}
int main() {
	int testcase, K;
	build();
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &K);
		int ret = 0;
		for(int i = 0; i < n; i++) {
			ret = ret << 1;
			ret |= ouroboros[n][(i + K)%olen[n]] - '0';
		}
		printf("%d\n", ret);
	}
	return 0;
}
