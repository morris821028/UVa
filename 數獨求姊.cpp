#include<stdio.h>
#include<stdlib.h>
#define Maxv 100000
struct DacingLinks {
	int left, right;
	int up, down;
	int data, ch, rh;
}DL[100001 + 1001];
int s[1001], o[1001], head, size;
int n, m, a, b, c, tn, Ans;
int Score[10][10]={
                    {6,6,6,6, 6,6,6,6,6},
                    {6,7,7,7, 7,7,7,7,6},
                    {6,7,8,8, 8,8,8,7,6},
                    {6,7,8,9, 9,9,8,7,6},
                    {6,7,8,9,10,9,8,7,6}, 
                    {6,7,8,9, 9,9,8,7,6},
                    {6,7,8,8, 8,8,8,7,6},
                    {6,7,7,7, 7,7,7,7,6},
                    {6,6,6,6, 6,6,6,6,6},
                    };
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
void board(int k) {
	static int set[81], a, b;
	int sum = 0;
	for(a = 0; a < k; a++) {
		set[DL[o[a]].data] = DL[o[a]].rh+1;
	}
	for(a = 0; a < n; a++) {
		for(b = 0; b < n; b++) {
			sum += Score[a][b]*set[a*n+b];
		}
	}
	Ans = Ans > sum ? Ans : sum; 
}
void DFS(int k) {
	if(DL[head].right == head) {
		board(k);
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
void new_row(int n, int Row[], int rh, int set) {
	int a, r, row = -1, k;
	for(a = 0; a < n; a++) {
		r = Row[a];
		DL[size].ch = r, DL[size].data = set, s[r]++;
		if(row == -1) {
			row = new_node(DL[DL[r].ch].up, DL[r].ch, size, size);
			DL[row].rh = rh;
		}else {
			k = new_node(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
			DL[k].rh = rh;
		}
	}
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
	int map[10][10], Row[10], t;
	n = 3;
	tn = n, n *= n, m = n*n*4, init(m);
	for(a = 0; a < n; a++)
		for(b = 0; b < n; b++) {
			scanf("%d", &map[a][b]);
			if(map[a][b] == 0) {
				for(c = 0; c < n; c++) {
					t = 0;
					Row[t++] = a*n + b + 1;
					Row[t++] = n*n + a*n + c + 1;
					Row[t++] = 2*n*n+ b*n + c + 1;
					Row[t++] = 3*n*n+ (a/tn*tn + b/tn)*n + c + 1;
					new_row(t, Row, c, a*n+b);
				}
			} else {
				c = map[a][b]-1, t = 0;
				Row[t++] = a*n + b + 1;
				Row[t++] = n*n + a*n + c + 1;
				Row[t++] = 2*n*n+ b*n + c + 1;
				Row[t++] = 3*n*n+ (a/tn*tn + b/tn)*n + c + 1;
				new_row(t, Row, c, a*n+b);
			}
		}
	Ans = 0, DFS(0);
	printf("%d\n", Ans);
	return 0;
}
