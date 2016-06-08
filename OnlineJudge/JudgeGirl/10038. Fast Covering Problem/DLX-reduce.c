#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#define MAXNODE 100000
#define MAXCOL 5005
#define MAXN 5005
struct DancingNode {
    int left, right, up, down;
    int ch, rh;
} DL[MAXNODE];
struct HelperNode {
	int head, size, next, prev;
} HN[MAXNODE];
int help_head;
int s[MAXCOL];
int head, size, Ans, Dep;
int markStk[MAXNODE], markIdx = -1;
void Remove(int c) {
    for (int i = DL[c].down; i != c; i = DL[i].down) {
    	if (HN[DL[i].rh].head == i)
    		HN[DL[i].rh].head = DL[i].left;
    	HN[DL[i].rh].size--;
        DL[DL[i].right].left = DL[i].left;
        DL[DL[i].left].right = DL[i].right;
        s[DL[i].ch]--;
    }
}
void Resume(int c) {
    for (int i = DL[c].down; i != c; i = DL[i].down) {
    	if (HN[DL[i].rh].head == i)
    		HN[DL[i].rh].head = DL[i].right;
    	HN[DL[i].rh].size++;
        DL[DL[i].right].left = i;
        DL[DL[i].left].right = i;
        s[DL[i].ch]++;
    }
}
void Reduce(int i) {
	int t = DL[i].rh;
	HN[HN[t].next].prev = HN[t].prev;
    HN[HN[t].prev].next = HN[t].next;
	s[DL[i].ch]--;
	DL[DL[i].down].up = DL[i].up;
	DL[DL[i].up].down = DL[i].down;
	for (int k = DL[i].right; k != i; k = DL[k].right) {
		DL[DL[k].down].up = DL[k].up;
		DL[DL[k].up].down = DL[k].down;
        s[DL[k].ch]--;
    }
}
void Recover(int i) {
	int t = DL[i].rh;
	HN[HN[t].next].prev = t;
    HN[HN[t].prev].next = t;
	s[DL[i].ch]++;
	DL[DL[i].down].up = i;
	DL[DL[i].up].down = i;
	for (int k = DL[i].right; k != i; k = DL[k].right) {
		DL[DL[k].down].up = k;
		DL[DL[k].up].down = k;
        s[DL[k].ch]++;
	}
}
void Select(int i) {
	int s = DL[i].rh;
	HN[HN[s].next].prev = HN[s].prev;
	HN[HN[s].prev].next = HN[s].next;
    Remove(i);
    for (int j = DL[i].right; j != i; j = DL[j].right)
		Remove(j);
	Dep++;
}
void Cancel(int i) {
	int s = DL[i].rh;
    for (int j = DL[i].right; j != i; j = DL[j].right)
		Resume(j);
    Resume(i);    
    HN[HN[s].next].prev = s;
	HN[HN[s].prev].next = s;
	Dep--;
}
int Decision() {
	int has = 0;
	for (int i = DL[head].right; i != head; i = DL[i].right) {
		if (s[i] == 1) {
			Select(DL[i].down);
			markStk[++markIdx] = DL[i].down;
			has = 1;
		}
	}
	return has;
}
int Subset(int x, int y) {	// 0: x in y, 1: y in x 
    assert(DL[x].ch == DL[y].ch);
    int a = 0, b = 0;
    int i, j;
    for (i = DL[x].right, j = DL[y].right; i != x && j != y; ) {
        if (DL[i].ch == DL[j].ch)
            i = DL[i].right, j = DL[j].right;
        else if (DL[i].ch < DL[j].ch)
            i = DL[i].right, a = 1;
        else
            j = DL[j].right, b = 1;
        if (a && b)
            break;
    }
    if (i != x)    a = 1;
    if (j != y)    b = 1;
    return a || b ? (a - b) : 1;
}
int Duplicate() {
	int has = 0;
	for (int i = DL[head].right; i != head; i = DL[i].right) {
		for (int j = DL[i].down; j != i; j = DL[j].down) {
			for (int k = DL[j].down; k != j && k != i; k = DL[k].down) {
				int cmp = Subset(j, k);
	            if (cmp == 0)
	                continue;
	            if (cmp == 1) {
                	markStk[++markIdx] = j;
                	Select(j);
            	} else {
            		markStk[++markIdx] = k;
                	Select(k);
				}
                has = 1;
			}
		}
	}
	return has;
}
int H(int limit) {
    static int c, ret, i, j, time = 0;
	static int used[MAXCOL] = {};
    for (c = DL[head].right, ++time, ret = 0; c != head; c = DL[c].right) {
        if (used[c] == time)
        	continue;
    	ret ++, used[c] = time;
    	if (ret >= limit)	return ret;
        for (i = DL[c].down; i != c; i = DL[i].down) {
            for (j = DL[i].right; j != i; j = DL[j].right)
            	used[DL[j].ch] = time;
        }
    }
    return ret;
}
void DFS() {
    int hval = H(Ans - Dep);
    if (DL[head].right == head && Dep < Ans)
    	Ans = Dep;
	if (Dep + hval >= Ans)
		return ;
	int cover_max = -1, cover_idx = -1;
	for (int i = HN[help_head].next; i != help_head; i = HN[i].next) {
		if (HN[i].size > cover_max) {
			cover_max = HN[i].size;
			cover_idx = HN[i].head;
		}
	}
	
	Select(cover_idx);
    DFS();
	Cancel(cover_idx);
	
	Reduce(cover_idx);
	int markEsp = markIdx;
	while (!Decision() && !Duplicate());
	DFS();
	while (markIdx > markEsp)
        Cancel(markStk[markIdx--]);
	Recover(cover_idx);
}
int new_node(int up, int down, int left, int right) {
    DL[size].up = up, DL[size].down = down;
    DL[size].left = left, DL[size].right = right;
    DL[up].down = DL[down].up = DL[left].right = DL[right].left = size;
    return size++;
}

void new_row(int n, int Row[], int rh) {
    int r, row = -1, k;
    int h = size;
    for (int i = 0; i < n; i++) {
        r = Row[i];
        DL[size].ch = r, s[r]++;
        DL[size].rh = rh;
        if (row == -1) {
            row = new_node(DL[DL[r].ch].up, DL[r].ch, size, size);
        } else {
            k = new_node(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
        }
    }
    HN[rh].size = n;
    HN[rh].head = h;
    HN[rh].next = HN[help_head].next;
    HN[rh].prev = help_head;
    HN[HN[help_head].next].prev = rh;
    HN[help_head].next = rh;
}
void init(int m) {
    size = 0;
    help_head = 0, HN[help_head].next = HN[help_head].prev = help_head;
    head = new_node(0, 0, 0, 0);
    int i;
    for (i = 1; i <= m; i++) {
        new_node(i, i, DL[head].left, head);
        DL[i].ch = i, s[i] = 0;
        DL[i].rh = 0;	// important pointer (fail pointer)
    }
}
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
    	int A[MAXN], B[MAXN];
		int toy[10005] = {}, R[MAXCOL];
		for (int i = 1; i <= n; i++) {
		    scanf("%d %d", &A[i], &B[i]);
		    toy[A[i]]++, toy[B[i]]++;
		}
		
		init(n);
		int run_id = 0;
		for (int i = 0; i <= 10000; i++) {
			int nt = 0;
			for (int j = 1; j <= n; j++) {
				if (A[j] == i || B[j] == i)
					R[nt++] = j;
			}
			if (nt) {
				run_id++;
				new_row(nt, R, run_id);
			}
		}
		Ans = n;
		Dep = 0, markIdx = -1;
		Decision();
		DFS();
		printf("%d\n", Ans);
		fflush(stdout);
	}
    return 0;
}
