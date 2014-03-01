#include<stdio.h>
#include<string.h>
#define oo 2147483647
#define Swap(x, y) {int t; t = x, x = y, y = t;}
struct {
	int x, y;
}link[400001], X[400001];
void Merge(int l, int m, int h) {
	int in1 = l, in2 = m+1;
	int i, j, Top = 0;
	while(in1 <= m && in2 <= h) {
		if(link[in1].x < link[in2].x || 
		(link[in1].x == link[in2].x && link[in1].y < link[in2].y))
			X[Top++] = link[in1++];
		else
			X[Top++] = link[in2++];
	}
	while(in1 <= m)	X[Top++] = link[in1++];
	while(in2 <= h) X[Top++] = link[in2++];
	for(i = 0, j = l; i < Top; i++, j++)
		link[j] = X[i];
}
void MergeSort(int l, int h) {
	if(l < h) {
		int m = (l + h)/2;
		MergeSort(l, m);
		MergeSort(m+1, h);
		Merge(l, m, h);
	}
}
int min(int x, int y) {
	return x < y ? x : y;
}
int max(int x, int y) {
	return x > y ? x : y;
}
int NodeT[200000], NodeL[200000];
int Parent[200000], Queue[200000], Used[200000];
int Down[200000][2], Up[200000];
int DownNode[200000][2];
void Solve(int n) {
	int i, j, k, Qt = -1, tn, tL;
	memset(Used, 0, sizeof(Used));
	memset(Down, 0, sizeof(Down));
	memset(Up, 0, sizeof(Up));
	Queue[++Qt] = 0, Used[0] = 1, Parent[0] = -1;
	for(i = 0; i < n; i++) {
		if(NodeT[i] == 1)
			Down[i][0] = 1;
		Parent[i] = -1;
	}
	for(i = 0; i <= Qt; i++) {
		tn = Queue[i];
		for(j = NodeL[tn], k = 0; k < NodeT[tn]; j++, k++) {
			if(link[j].y != Parent[tn]) {
				if(Used[link[j].y] == 0) {
					Used[link[j].y] = 1;
					Queue[++Qt] = link[j].y;
					Parent[link[j].y] = tn;
				}
			}
		}
	}
	for(i = Qt; i >= 0; i--) {
		tn = Queue[i];
		for(j = NodeL[tn], k = 0; k < NodeT[tn]; j++, k++) {
			if(link[j].y != Parent[tn]) {
				tL = Down[link[j].y][0]+1;
				if(tL > Down[tn][1]) {
					Swap(tL, Down[tn][1]);
					DownNode[tn][1] = link[j].y;
				}
				if(Down[tn][0] < Down[tn][1]) {
					Swap(Down[tn][0], Down[tn][1]);
					Swap(DownNode[tn][0], DownNode[tn][1]);
				}
			}
		}
	}
	for(i = 0; i <= Qt; i++) {
		tn = Queue[i];
		for(j = NodeL[tn], k = 0; k < NodeT[tn]; j++, k++) {
			if(link[j].y != Parent[tn]) {
				tL = Down[tn][0];
				if(DownNode[tn][0] == link[j].y)
					tL = Down[tn][1];
				tL = max(Up[tn]+1, tL);
				Up[link[j].y] = max(tL, Up[link[j].y]);
			}
		}
	}
	/*Reuse NodeT[]*/
	int maxL = 0;
	for(i = 0; i < n; i++) {
		NodeT[i] = max(Down[i][0]+Down[i][1]-1, Down[i][0]+Up[i]);
		maxL = max(maxL, NodeT[i]);
	}
	for(i = 0; i < n; i++)
		if(maxL == NodeT[i])
			printf("%d\n", i);
}
main() {
	int n, m, i, j;
	while(scanf("%d", &n) == 1) {
		for(i = 0; i < n-1; i++) {
			scanf("%d %d", &link[i].x, &link[i].y);
			link[n-1+i].x = link[i].y, link[n-1+i].y = link[i].x;
		}
		m = n*2-3;
		MergeSort(0, m);
		for(i = 0; i < n; i++)
			NodeT[i] = 0, NodeL[i] = oo;
		for(i = 0; i <= m; i++) {
			NodeL[link[i].x] = min(NodeL[link[i].x], i);
			NodeT[link[i].x]++;
		}
		Solve(n);
	}
	return 0;
}
