#include<stdio.h>
#include<stdlib.h>
#define oo 2147483647
typedef struct {
	int wait, time;
}D;
D Cust[61], X[61];
void Merge(int l, int m, int r) {
	int In1 = l, In2 = m+1;
	int a, b, Top = 0;
	while(In1 <= m && In2 <= r)
		if(Cust[In1].wait < Cust[In2].wait || 
		(Cust[In1].wait == Cust[In2].wait && Cust[In1].time < Cust[In2].time))
			X[Top++] = Cust[In1++];
		else
			X[Top++] = Cust[In2++];
	while(In1 <= m)	X[Top++] = Cust[In1++];
	while(In2 <= r) X[Top++] = Cust[In2++];
	for(a = 0, b = l; a < Top; a++, b++)
		Cust[b] = X[a];
}
void MergeSort(int l, int r) {
	if(l < r) {
		int m = (l+r)/2;
		MergeSort(l, m);
		MergeSort(m+1, r);
		Merge(l, m, r);
	}
}
int n, a, Ans, bike[61] = {};
void DFS(int now, int time) {
	if(now == n) {
		if(time < Ans)
			Ans = time;
		return;
	}
	if(time >= Ans)	return;
	int a, t;
	for(a = 0; a <= time; a++) {
		if(bike[a] < Cust[now].wait+30) {
			t = bike[a];
			if(bike[a] >= Cust[now].wait)
				bike[a] = bike[a] + Cust[now].time;
			else
				bike[a] = Cust[now].wait + Cust[now].time;
			DFS(now+1, time);
			bike[a] = t;
		}
	}
	bike[time+1] = Cust[now].time + Cust[now].wait;
	DFS(now+1, time+1);
}
main() {
	while(scanf("%d", &n) == 1) {
		for(a = 0; a < n; a++)
			scanf("%d %d", &Cust[a].wait, &Cust[a].time);
		MergeSort(0, n-1);
		Ans = oo, DFS(0, -1);
		printf("%d\n", Ans+1);
	}
	return 0;
}
