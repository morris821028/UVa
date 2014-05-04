#include <stdio.h>
#include <map>
#include <string.h>
#include <algorithm>
using namespace std;
int pSIZE, pCOUNT;
int Pval[256][256], Ppre[256][256], Plen[256];
int A[65536], P[65536];

void build(int n) {
	int pxIdx = -1, pyIdx = pSIZE;
	map<int, int> PREV;
	map<int, int>::iterator it;
	
	memset(Plen, 0, sizeof(Plen));
	
	for(int i = 0; i < n; i++) {
		if(pyIdx == pSIZE)
			pxIdx++, pyIdx = 0;
		Pval[pxIdx][pyIdx] = A[i];
		it = PREV.find(A[i]);
		if(it == PREV.end()) {
			Ppre[pxIdx][pyIdx] = -1;
			PREV[A[i]] = i;
		} else {
			Ppre[pxIdx][pyIdx] = it->second;
			it->second = i;
		}
		P[i] = Ppre[pxIdx][pyIdx];
		pyIdx++;
		Plen[pxIdx] = pyIdx;
	}
	
	pCOUNT = pxIdx + 1;
	
	for(int i = 0; i < pCOUNT; i++) {
		sort(Pval[i], Pval[i] + Plen[i]);
		sort(Ppre[i], Ppre[i] + Plen[i]);
	}
}
int query(int L, int R) {
	int B = L;
	int ret = 0;
	while(L%pSIZE && L <= R) {
		if(P[L] < B)	ret++;
		L++;
	}
	while((R+1)%pSIZE && L <= R) {
		if(P[R] < B)	ret++;
		R--;
	}
	if(L > R)	return ret;
	L /= pSIZE, R /= pSIZE;
	while(L <= R) {
		int cnt = upper_bound(Ppre[L], Ppre[L] + pSIZE, B - 1) - Ppre[L];
		ret += cnt;
		L++;
	}
	return ret;
}
void updatePrev(int x) {
	for(int i = x * pSIZE, j = 0; j < Plen[x]; i++, j++)
		Ppre[x][j] = P[i];
	sort(Ppre[x], Ppre[x] + Plen[x]);
}
void update(int x) {
    for(int i = x * pSIZE, j = 0; j < Plen[x]; i++, j++)
		Pval[x][j] = A[i], Ppre[x][j] = P[i];
	sort(Pval[x], Pval[x] + Plen[x]);
	sort(Ppre[x], Ppre[x] + Plen[x]);
}
void getNext(int x, int val, int &NEXT, int &nx) {
	int y = x/pSIZE * pSIZE + Plen[x / pSIZE] - 1;
	NEXT = 0x3f3f3f3f, nx = -1;
	while(x%pSIZE && x <= y) {
		if(A[x] == val) {
			NEXT = x, nx = x / pSIZE;
			return;
		}
		x++;
	}
	int L = x / pSIZE, R = pCOUNT - 1;
	if(L * pSIZE < x)	return;
	for(int i = L; i <= R; i++) {
		int pos = binary_search(Pval[i], Pval[i] + Plen[i], val);
		if(pos == true) {
			NEXT = i * pSIZE;
			while(A[NEXT] != val)	NEXT++;
			nx = i;
			return;
		}
	}
}
void getPrev(int y, int val, int &PREV, int &px) {
	int x = 0;
	PREV = -1, px = -1;
	while((y+1)%pSIZE && x <= y) {
		if(A[y] == val) {
			PREV = y, px = y / pSIZE;
			return;
		}
		y--;
	}
	int L = 0, R = y / pSIZE;
	if(R * pSIZE > y)	return;
	for(int i = R; i >= L; i--) {
        int pos = binary_search(Pval[i], Pval[i] + Plen[i], val);
		if(pos == true) {
			PREV = i * pSIZE + Plen[i] - 1;
			while(A[PREV] != val)	PREV--;
			px = i;
			return;
		}
	}
}
void modify(int X, int nval) {
	if(A[X] == nval)	return ;
	int oval = A[X];
	int NEXT, PREV, nx, px;
	PREV = P[X], px = -1;
	if(PREV >= 0)	px = PREV / pSIZE;
	
	getNext(X + 1, oval, NEXT, nx);
	if(nx != -1) {
		P[NEXT] = PREV;
		updatePrev(nx);
	}
    
	getNext(X + 1, nval, NEXT, nx);
	if(nx != -1) {
		P[NEXT] = X;
		updatePrev(nx);
	}
    
	getPrev(X - 1, nval, PREV, px);
	A[X] = nval, P[X] = PREV;
	update(X / pSIZE);
}
int main() {
    //	freopen("in.txt", "r+t", stdin);
    //	freopen("out2.txt", "w+t", stdout);
	int n, m, L, R;
	char cmd[4];
	while(scanf("%d %d", &n, &m) == 2) {
		for(pSIZE = 1; pSIZE * pSIZE < n; pSIZE++);
		
		for(int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		build(n);
		
		while(m--) {
			scanf("%s %d %d", cmd, &L, &R);
			if(cmd[0] == 'Q') {
				R--;
				int r = query(L, R);
				printf("%d\n", r);
			} else {
				modify(L, R);
			}
		}
	}
	return 0;
}
/*
 30 50
 4 19 18 17 16 7 16 9 18 14 4 11 4 2 8 8 1 3 1 5 5 8 3 8 11 17 10 0 2 16
 M 20 12 
 Q 2 29
 M 8 9
 Q 7 7
 M 25 12
 M 19 13
 Q 12 22
 Q 8 11
 M 5 5
 M 15 8
 Q 9 26
 */
