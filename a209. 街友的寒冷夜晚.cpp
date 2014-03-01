/**********************************************************************************/
/*  Problem: a209 "街友的寒冷夜晚" from 重複覆蓋問題                 */
/*  Language: C                                                                   */
/*  Result: AC (400ms, 288KB) on ZeroJudge                                        */
/*  Author: morris1028 at 2011-08-09 07:16:52                                     */
/**********************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Maxv 100000
struct DacingLinks {
	int left, right;
	int up, down;
	int data, ch, rh;
}DL[401*400 + 401];
int s[401], o[8001], head, size, Ans;
struct Data {
	int l, a, b;
}Data[8000];
void Remove(int c) {
	static int i;
	for(i = DL[c].down; i != c; i = DL[i].down) {
		DL[DL[i].right].left = DL[i].left;
		DL[DL[i].left].right = DL[i].right;
		s[DL[i].ch]--;
	}
}
void Resume(int c) {
	static int i;
	for(i = DL[c].down; i != c; i = DL[i].down) {
		DL[DL[i].right].left = i;
		DL[DL[i].left].right = i;
		s[DL[i].ch]++;
	}
}
int used[401] = {};
int H() {
	static int c, ret, i, j, time = 0;
	for(c = DL[head].right, ++time, ret = 0; c != head; c = DL[c].right) {
		if(used[c] != time) {
			ret ++, used[c] = time;
			for(i = DL[c].down; i != c; i = DL[i].down)
				for(j = DL[i].right; j != i; j = DL[j].right)
					used[DL[j].ch] = time;
		}
	}
	return ret;
}
void DFS(int k) {
	if(k + H() >= Ans)	return;
	if(DL[head].right == head) {
		if(k < Ans)	Ans = k;
		return;
	}
	int t = Maxv, c, i, j;
	for(i = DL[head].right; i != head; i = DL[i].right) {
		if(s[i] < t) {
			t = s[i], c = i;
		}
	}
	for(i = DL[c].down; i != c; i = DL[i].down) {
		Remove(i);
		for(j = DL[i].right; j != i; j = DL[j].right)	Remove(j);
		DFS(k+1);
		for(j = DL[i].left; j != i; j = DL[j].left)		Resume(j);
		Resume(i);
	}
}
int new_node(int up, int down, int left, int right) {
	DL[size].up = up, DL[size].down = down;
	DL[size].left = left, DL[size].right = right;
	DL[up].down = DL[down].up = DL[left].right = DL[right].left = size;
	return size++;
}
void new_row(int n, int Row[]) {
	int a, r, row = -1, k;
	for(a = 0; a < n; a++) {
		r = Row[a];
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
void init(int m) {
	size = 0;
	head = new_node(0, 0, 0, 0);
	int i;
	for(i = 1; i <= m; i++) {
		new_node(i, i, DL[head].left, head);
		DL[i].ch = i, s[i] = 0;
	}
} 
int min(int x, int y) {
	return x < y ? x : y;
}
int max(int x, int y) {
	return x > y ? x : y;
}
void QuickSort(int , int );
main() {
	int m, n, a, b, c, d, e, x;
	while(scanf("%d %d", &m, &n) == 2) {
		if(n == 0 && m == 0) break;
		int map[21][21] = {};
		for(a = 1; a <= n; a++)
			for(b = 1; b <= m; b++)
				scanf("%d", &map[a][b]);
		int DP[21][21] = {}, Row[401], t = 0, rr = 0;
		int Cut[21][21] = {}, tag[21][21] = {}, Yestag = 0;
		for(a = 1; a <= n; a++) {
			for(b = 1; b <= m; b++) {
				if(map[a][b]) {
					DP[a][b] = DP[a-1][b-1];
					DP[a][b] = DP[a][b] < DP[a][b-1] ? DP[a][b] : DP[a][b-1];
					DP[a][b] = DP[a][b] < DP[a-1][b] ? DP[a][b] : DP[a-1][b];
					DP[a][b]++;
					for(c = a-DP[a][b]+1; c <= a; c++)
						for(d = b-DP[a][b]+1; d <= b; d++) {
							if(c == a && d == b) continue;
							x = min(c -(a-DP[a][b]+1)+1, d-(b-DP[a][b]+1)+1);
							Cut[c][d] = max(Cut[c][d], x);
						}
					Yestag ++, tag[a][b] = Yestag;
				}
			}
		}
		for(a = 1; a <= n; a++) {
			for(b = 1; b <= m; b++) {
				if(map[a][b] && DP[a][b] > Cut[a][b]) {
					Data[rr].l = DP[a][b], Data[rr].a = a, Data[rr].b = b, rr++;
				}
			}
		}
		init(Yestag), QuickSort(0, rr-1);
		for(a = 0; a < rr; a++) {
			e = Data[a].l, t = 0;
			for(c = Data[a].a-e+1; c <= Data[a].a; c++)
				for(d = Data[a].b-e+1; d <= Data[a].b; d++)
					if(tag[c][d])
						Row[t++] = tag[c][d];
			new_row(t, Row);
		}
		Ans = Maxv,	DFS(0);
		printf("%d\n", Ans);
	}
	return 0;
}
void Swap(int x, int y) {
    int t;
    t = Data[x].l, Data[x].l = Data[y].l, Data[y].l = t;
	t = Data[x].a, Data[x].a = Data[y].a, Data[y].a = t;
	t = Data[x].b, Data[x].b = Data[y].b, Data[y].b = t;
}
int split(int l, int r) {
    int a = l, b, t = Data[l].l;
    for(b = l+1; b <= r; b++) {
        if(Data[b].l >= t)
            a++, Swap(a, b);
    }
    Swap(l, a);
    return a;
}
void QuickSort(int l, int r) {
    if(l < r) {
        int v = l + rand()%(r-l);
        Swap(l, v);
        int m = split(l, r);
        QuickSort(l, m-1);
        QuickSort(m+1, r);
    }
}
