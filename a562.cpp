#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
struct Node {
	unsigned int state[2];
	char f, g, x, y;
};
struct cmp {
    bool operator() (Node a, Node b) {
        if(a.f != b.f)
            return a.f < b.f;
        return a.g < b.g;
    }
};
priority_queue<Node, vector<Node>, cmp> pQ;
int gm[10][10];
int solve(int n) {
	int i, j, k, h, g, bit;
	int ttx, tty, tx, ty, x, y;
	int ans = 0, num;
	int dir[4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
	int Q[505][2], Qt;
	char o_app[105], g_app[105], t_map[n][n];
    Node tn, bn;
    int test = 0;
	while(!pQ.empty()) {
        tn = pQ.top();
        bn = tn;
        pQ.pop();
        if(tn.f <= ans) continue;
        memset(o_app, 0, sizeof(o_app));
		for(i = 0; i < 2; i++) {
			for(j = 0; j < 32; j++) {
				if((tn.state[i]&(1<<j))) {
				    num = (i<<5)+j;
					tx = num/n, ty = num%n;
					o_app[gm[tx][ty]] = 1;
				}
			}
		}
		ans = ans > tn.g ? ans : tn.g;
		if(tn.f == tn.g)	break;
        bn.g = tn.g+1;
		for(i = 0; i < 4; i++) {
			x = tn.x+dir[i][0], y = tn.y+dir[i][1];
			if(x < 0 || y < 0 || x >= n || y >= n)
                continue;
            if(o_app[gm[x][y]])
                continue;
            memset(g_app, 0, sizeof(g_app));
            memset(t_map, 0, sizeof(t_map));
            bn.x = x, bn.y = y;
            Qt = 0, Q[Qt][0] = x, Q[Qt][1] = y;
            g_app[gm[x][y]] = 1, h = 0;
            t_map[x][y] = 1;
            for(j = 0; j <= Qt; j++) {
                tx = Q[j][0], ty = Q[j][1];
                for(k = 0; k < 4; k++) {
                    ttx = tx+dir[k][0], tty = ty+dir[k][1];
                    if(ttx < 0 || tty < 0 || ttx >= n || tty >= n)
                        continue;
                    if(o_app[gm[ttx][tty]])
                        continue;
                    if(!g_app[gm[ttx][tty]])
                        h++;
                    g_app[gm[ttx][tty]] = 1;
                    if(!t_map[ttx][tty]) {
                        t_map[ttx][tty] = 1;
                        Qt++;
                        Q[Qt][0] = ttx, Q[Qt][1] = tty;
                    }
                }
            }
            if(bn.g+h <= ans)	continue;
            bit = bn.x*n + bn.y;
            bn.state[bit>>5] |= (1<<(bit&31));
            bn.f = bn.g+h;
            pQ.push(bn);
            bn.state[bit>>5] ^= (1<<(bit&31));
        }
    }
	return ans;
}
int main() {
    int t, n, i, j;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		Node tn;
		memset(&tn, 0, sizeof(tn));
		tn.f = n*n, tn.g = 1;
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				scanf("%d", &gm[i][j]);
				tn.state[(i*n+j)>>5] |= (1<<((i*n+j)&31));
				tn.x = i, tn.y = j;
				pQ.push(tn);
				tn.state[(i*n+j)>>5] ^= (1<<((i*n+j)&31));
			}
		}
		printf("%d\n", solve(n));
		while(!pQ.empty())  pQ.pop();
	}
    return 0;
}
