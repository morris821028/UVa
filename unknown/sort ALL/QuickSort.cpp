#include<stdio.h>
#include<stdlib.h>
int Data[500001];
void Swap(int x, int y) {
	int t;
	t = Data[x], Data[x] = Data[y], Data[y] = t;
}
int split(int l, int r) {
	int a = l, b, t = Data[l];
	for(b = l+1; b <= r; b++) {
		if(Data[b] <= t)
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
main() {
	int n = 0, a;
	while(scanf("%d", &Data[n]) == 1)
		n++;
	QuickSort(0, n-1);
	for(a = 0; a < n; a++)
		printf("%d ", Data[a]);
	return 0;
}
