#include<stdio.h>
#include<stdlib.h>
#define Maxv 100000
struct DacingLinks {
	int left, right;
	int up, down;
	int data, ch, rh;
}DL[100001 + 1001];
int s[1001], o[1001], head, len, size;
void Remove(int c) {
	DL[DL[c].right].left = DL[c].left;
	DL[DL[c].left].right = DL[c].right;
	int i, j;
	for(i = DL[c].down; i != c; i = DL[i].down) {
		for(j = DL[i].right; j != i; j = DL[j].right) {
			DL[DL[j].down].up = DL[j].up;
			DL[DL[j].up].down = DL[j].down;
			s[DL[j].ch]--;
		}
	}
}
void Resume(int c) {
	int i, j;
	for(i = DL[c].down; i != c; i = DL[i].down) {
		for(j = DL[i].left; j != i; j = DL[j].left) {
			DL[DL[j].down].up = j;
			DL[DL[j].up].down = j;
			s[DL[j].ch]++;
		}
	}
	DL[DL[c].right].left = c;
	DL[DL[c].left].right = c;
}
void DFS(int k) {
	if(k > len) return;
	if(DL[head].right == head) {
		if(k < len) len = k;
		return;
	}
	int t = Maxv, c, i, j;
	for(i = DL[head].right; i != head; i = DL[i].right) {
		if(s[i] < t) {
			t = s[i], c = i;
		}
	}
	Remove(c);
	for(i = DL[c].down; i != c; i = DL[i].down) {
		o[k] = i;
		for(j = DL[i].right; j != i; j = DL[j].right)
			Remove(DL[j].ch);
		DFS(k+1);
		for(j = DL[i].left; j != i; j = DL[j].left)
			Resume(DL[j].ch);
	}
	Resume(c);
}
int new_node(int up, int down, int left, int right) {
	DL[size].up = up, DL[size].down = down;
	DL[size].left = left, DL[size].right = right;
	DL[up].down = DL[down].up = DL[left].right = DL[right].left = size;
	return size++;
}
void init(int m) {
	size = 0;
	head = new_node(0, 0, 0, 0);
	int i;
	for(i = 1; i <= m; i++) {
		new_node(i, i, DL[head].left, head);
		DL[i].ch = i, s[i] = 0;
	}
} 
main() {
	int n, m, a, b, x, r, k, C = 0;
	while(scanf("%d %d", &n, &m) != EOF) {
		init(m);
		for(a = 1; a <= n; a++) {
			scanf("%d", &x);
			int row = -1;
			while(x--) {
				scanf("%d", &r);
				DL[size].ch = r, s[r]++;
				if(row == -1) {
					row = new_node(DL[DL[r].ch].up, DL[r].ch, size, size);
					DL[row].rh = a;
				}else {
					k = new_node(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
					DL[k].rh = a;
				}
			}
		}
		len = Maxv,	DFS(0);
		if(len != Maxv)	printf("%d\n", len);
		else	puts("No");
	}
	return 0;
}
