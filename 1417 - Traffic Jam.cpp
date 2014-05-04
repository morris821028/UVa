#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

struct Node {
	int c[6];
}; // - \ / _ | |
Node ST[262144 + 10];

void build(int k, int l, int r) {
	if(l > r)	return;
	if(l == r) {
		memset(&ST[k], 0, sizeof(ST[k]));
		return;
	}
	int mid = (l + r)/2;
	build(k<<1, l, mid);
	build(k<<1|1, mid+1, r);
}
Node combine(Node s1, Node s2) {
	Node s;
	s.c[0] = (s1.c[0] && s2.c[0]) || (s1.c[1] && s2.c[2]);
	s.c[1] = (s1.c[0] && s2.c[1]) || (s1.c[1] && s2.c[3]);
	s.c[2] = (s1.c[2] && s2.c[0]) || (s1.c[3] && s2.c[2]);
	s.c[3] = (s1.c[2] && s2.c[1]) || (s1.c[3] && s2.c[3]);
	s.c[4] = (s1.c[4]) || (s1.c[0] && s2.c[4] && s1.c[3]);
	s.c[5] = (s2.c[5]) || (s2.c[0] && s1.c[5] && s2.c[3]);
	return s;
}
void modify(int k, int l, int r, int qidx, int qfield, int qval) {
	if(l > r)	return;
	if(l == r) {
		ST[k].c[qfield] = qval;
		ST[k].c[1] = (ST[k].c[0] && ST[k].c[5]) || (ST[k].c[3] && ST[k].c[4]);
		ST[k].c[2] = (ST[k].c[0] && ST[k].c[4]) || (ST[k].c[3] && ST[k].c[5]);
		return;
	}
	int mid = (l + r)/2;
	if(qidx > mid)
		modify(k<<1|1, mid+1, r, qidx, qfield, qval);
	else
		modify(k<<1, l, mid, qidx, qfield, qval);
	ST[k] = combine(ST[k<<1], ST[k<<1|1]);
}
Node query(int k, int l, int r, int ql, int qr) {
	if(ql <= l && r <= qr)
		return ST[k];
	int mid = (l + r)/2;
	if(ql > mid)
		return query(k<<1|1, mid+1, r, ql, qr);
	else if(qr <= mid)
		return query(k<<1, l, mid, ql, qr);
	else
		return combine(query(k<<1, l, mid, ql, qr), 
						query(k<<1|1, mid+1, r, ql, qr));
}
int main() {
	//freopen("in.txt", "r+t", stdin);
	//freopen("out2.txt", "w+t", stdout);  
	int testcase, C;
	int r1, r2, c1, c2;
	int lines = 0;
	char cmd[10];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &C);
		memset(ST, 0, sizeof(ST));
		build(1, 0, C);
		while(scanf("%s", cmd) == 1 && cmd[0] != 'E') {
			scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
			if(cmd[0] == 'O' || cmd[0] == 'C') { // open
				int qval = cmd[0] == 'O' ? 1 : 0;
				if(c1 != c2) {
					modify(1, 0, C, min(c1, c2), r1 == 1 ? 0 : 3, qval);
				} else {
					modify(1, 0, C, min(c1, c2) - 1, 5, qval);
					modify(1, 0, C, min(c1, c2), 4, qval);
				}
			} else { // ask
				if(c1 > c2)
					swap(c1, c2), swap(r1, r2);
				
				if(r1 == r2 && c1 == c2) {
					puts("Y");
				} else if(r1 != r2 && c1 == c2) {
					Node l = query(1, 0, C, 0, c1 - 1);
					Node r = query(1, 0, C, c1, C);
					if(l.c[5] || r.c[4])
						puts("Y");
					else
						puts("N");
				} else {
					Node l = query(1, 0, C, 0, c1 - 1);
					Node r = query(1, 0, C, c2, C);
					Node m = query(1, 0, C, c1, c2 - 1);
					int kc[2][2] = {{0, 1}, {2, 3}};
					if(m.c[kc[r1 - 1][r2 - 1]] || 
						(l.c[5] && m.c[kc[(3 - r1) - 1][r2 - 1]]) ||
						(r.c[4] && m.c[kc[r1 - 1][(3 - r2) - 1]]) ||
						(l.c[5] && r.c[4] && m.c[kc[(3 - r1) - 1][(3 - r2) - 1]]))
						puts("Y");
					else
						puts("N");
				}
			}
		}
	}
	return 0;
}
/*
3
2
Open 1 1 1 2
Open 1 2 2 2
Ask 1 1 2 2
Ask 2 1 2 2
Exit
3
Open 1 1 1 2
Ask 1 1 1 2
Close 1 1 1 2
Ask 1 1 1 2
Exit
2
Open 1 1 1 2
Open 1 2 2 2
Open 2 1 2 2
Ask 1 1 2 1
Exit
*/
