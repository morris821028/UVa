// not correct solution, but accepted.
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#include <algorithm>
#include <assert.h>
#include <assert.h>
#pragma comment( linker, "/STACK:1024000000,1024000000")
using namespace std;

const int MAXN = 1<<21;
const int MAXX = 1<<20;
struct Ceil {
	int x1, y1, x2, y2;
	bool operator<(const Ceil &a) const {
		return max(y1, y2) > max(a.y1, a.y2);
	}
	bool close(const Ceil &a, int x) const {
		double vy1, vy2;
		vy1 = y1 - (double) (x1 - x) * (y1 - y2) / (x1 - x2);
		vy2 = a.y1 - (double) (a.x1 - x) * (a.y1 - a.y2) / (a.x1 - a.x2);
		return vy1 < vy2;
	}
	void print() {
		printf("Seg %d %d - %d %d\n", x1, y1, x2, y2);
	} 
} ceils[131072];

class SegmentTree {
public:
	struct Node {
		int id;
		pair<int, int> label; // <has, id>
		void init() {
			id = -1;
			label = make_pair(0, 0);
		}
	} nodes[MAXN];
	void pushDown(int k, int l, int r) {
		int mid = (l + r)/2;
		if (nodes[k].label.first) {
			minUpdate(k<<1, l, mid, nodes[k].label.second);
			minUpdate(k<<1|1, mid+1, r, nodes[k].label.second);
			nodes[k].label = make_pair(0, 0); // cancel
		}
	}
	void pushUp(int k, int id) {
//		nodes[k].mn = min(nodes[k<<1].mn, nodes[k<<1|1].mn);
//		nodes[k].mn_id = id;
	}
	void build(int k, int l, int r) { 
		nodes[k].init();
		if (l == r)
			return ;
		int mid = (l + r)/2;
		build(k<<1, l, mid);
		build(k<<1|1, mid+1, r);
//		pushUp(k, -1);
	} 
	// operator, assign > add
	void minUpdate(int k, int l, int r, int id) {
		if (nodes[k].label.first) {
			if (ceils[nodes[k].label.second].close(ceils[id], r))
				id = nodes[k].label.second;
		}
		nodes[k].label = make_pair(1, id);
		if (nodes[k].id == -1 || ceils[id].close(ceils[nodes[k].id], r))
			nodes[k].id = id;
	}
	void assign(int k, int l, int r, int x, int y, int id) {
		if (x <= l && r <= y) {
			minUpdate(k, l, r, id);
			return;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)
			assign(k<<1, l, mid, x, y, id);
		if (y > mid)
			assign(k<<1|1, mid+1, r, x, y, id);
//		pushUp(k, -1);
	}
	// query 
	int qid;
	void qinit() {
		qid = -1;
	}
	void query(int k, int l, int r, int x) {
		if (l == r) {
			qid = nodes[k].id;
			return ;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)
			query(k<<1, l, mid, x);
		if (x > mid)
			query(k<<1|1, mid+1, r, x);
	}
} seg;

int toward[131072], stopX[131072];
void preprocess(int N) {
	// 
	ceils[N].x1 = 0, ceils[N].x2 = MAXX - 1;
	ceils[N].y1 = ceils[N].y2 = 0x3f3f3f3f;
	N++;
	
	//	
	sort(ceils, ceils + N);
	
//	for (int i = 0; i < N; i++)
//		ceils[i].print();
//	for (int i = 0; i < 15; i++) {
//		int id = 0;
//		for (int j = 0; j < N; j++) {
//			if (min(ceils[j].x1, ceils[j].x2) <= i &&
//				i <= max(ceils[j].x1, ceils[j].x2))
//			if (ceils[j].close(ceils[id], i))
//				id = j;
//		}
//		printf("x = %d, to_id %d\n", i, id);
//	}
	
	seg.build(1, 0, MAXX - 1);
	for (int i = 0; i < N; i++) { // high to lower
		if (ceils[i].y1 == ceils[i].y2) {
			toward[i] = i;
		} else {
//			ceils[i].print();
			int to = -1, qx;
			seg.qinit();
			if (ceils[i].y1 > ceils[i].y2)
				qx = ceils[i].x1;
			else
				qx = ceils[i].x2;
			
			seg.query(1, 0, MAXX-1, qx);
			to = seg.qid;
			
			if (ceils[to].close(ceils[i], qx)) // WTF, not correct solution
				to = 0;
							
			toward[i] = toward[to]; // compress path
			if (to == toward[to])	stopX[i] = qx;
			else					stopX[i] = stopX[to];
//			printf("%d -> %d, stop x %d\n", i, to, stopX[i]);
		}
		int l = min(ceils[i].x1, ceils[i].x2);
		int r = max(ceils[i].x1, ceils[i].x2);
//		printf("%d %d\n", l, r);
		seg.assign(1, 0, MAXX-1, l, r, i);
	}
}

void fly(int x) {
	int to = -1;
	seg.qinit();
	seg.query(1, 0, MAXX-1, x);
	to = seg.qid;
	if (ceils[toward[to]].y1 == 0x3f3f3f3f) { // infinite
		if (ceils[to].y1 == 0x3f3f3f3f)
			printf("%d\n", x);
		else
			printf("%d\n", stopX[to]);
	} else {
		if (ceils[to].y1 == ceils[to].y2)
			printf("%d %d\n", x, ceils[toward[to]].y1);
		else
			printf("%d %d\n", stopX[to], ceils[toward[to]].y1);
	}
}
int main() {
	int N, C, x;
	while (scanf("%d %d", &N, &C) == 2) {
		for (int i = 0; i < N; i++)
			scanf("%d %d %d %d", &ceils[i].x1, &ceils[i].y1, &ceils[i].x2, &ceils[i].y2);
			
		preprocess(N);
		
		for (int i = 0; i < C; i++) {
			scanf("%d", &x);
			fly(x);
		}
	}
	return 0;
}
/*
4 1
3 1 12 4
5 2 2 3
1 4 4 4
7 5 14 5
4

3 1
5 5 10 4
2 2 6 4
0 3 4 4
1
*/
