#include<stdio.h>
#include<stdlib.h>
#define Swap(x, y) {int t; t = x, x = y, y = t;}
#define Maxv 100000
struct DacingLinks {
	int left, right;
	int up, down;
	int data, ch, rh;
}DL[20001];
int s[1001], o[1001], head, len, size, flag;
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
	if(flag > 1) return;
	if(DL[head].right == head) {
		flag++, len = k;
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
void new_row(int n, int Row[], int i) {
	int a, r, row = -1, k;
	for(a = 0; a < n; a++) {
		r = Row[a];
		DL[size].ch = r;
		s[r]++;
		if(row == -1) {
			row = new_node(DL[DL[r].ch].up, DL[r].ch, size, size);
			DL[row].rh = i;
		}else {
			k = new_node(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
			DL[k].rh = i;
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
typedef struct {
	int A, B;
}Data;
Data in[10001], out[10001];
int cmp(const void *a, const void *b) {
	Data *aa, *bb;
	aa = (Data *)a, bb = (Data *)b;
	if(bb->A < aa->A)	return 1;
	return 0;
}
main() {
	int n, m, a, b, Row[2], T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		init(n);
		for(a = 1; a <= m; a++) {
			scanf("%d %d", &Row[0], &Row[1]);
			if(Row[0] > Row[1])
				Swap(Row[0], Row[1]);
			in[a].A = Row[0], in[a].B = Row[1];
			new_row(2, Row, a);
		}
		len = Maxv,	flag = 0, DFS(0);
		if(flag == 1)	{
			printf("YES\n");
			for(a = 0; a < len; a++)
				out[a] = in[DL[o[a]].rh];
			qsort(out, len, sizeof(Data), cmp);
			for(a = 0; a < len; a++)
				printf("%d %d\n", out[a].A, out[a].B);
		}
		else	puts("NO");
	}
	return 0;
}
