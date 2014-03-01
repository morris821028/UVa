#include<stdio.h>
int Parent[100001], Rank[100001], total;
struct link {
	int x, y;
	float w;
}Data[100000], X[100000];
void Merge(int l, int m, int h) {
	int In1 = l, In2 = m+1;
	int a, b, Top = 0;
	while(In1 <= m && In2 <= h) {
		if(Data[In1].w > Data[In2].w) {
			X[Top++] = Data[In1++];
		}
		else {
			X[Top++] = Data[In2++];
		}
	}
	while(In1 <= m) X[Top++] = Data[In1++];
	while(In2 <= h) X[Top++] = Data[In2++];
	for(a = 0, b = l; a < Top; a++, b++)
		Data[b] = X[a];
}
void MergeSort(int l, int h) {
	if(l < h) {
		int m = (l+h)/2;
		MergeSort(l, m);
		MergeSort(m+1, h);
		Merge(l, m, h);
	}
}
void MakeSet(int N) {
	int a;
    for(a = 0; a <= N; a++)
        Parent[a] = a, Rank[a] = 1; 
} 
int FindSet(int x) {
    if(x != Parent[x])
        Parent[x] = FindSet(Parent[x]);
    return Parent[x];
}
void Link(int x, int y) {
    if(Rank[x] > Rank[y])
        Parent[y] = x, Rank[x] += Rank[y];
    else
        Parent[x] = y, Rank[y] += Rank[x];
} 
void Union(int x, int y) {
    x = FindSet(x), y = FindSet(y);
    if(x != y)
        Link(x, y), total++;
} 
main() {
	int T, n, m, a;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		for(a = 0; a < m; a++) {
			scanf("%d %d %f", &Data[a].x, &Data[a].y, &Data[a].w);
		}
		if(n == 1) {puts("No way.");continue;}
		MakeSet(n);
		MergeSort(0, m-1);
		for(a = 0, total = 0; a < m; a++) {
			Union(Data[a].x, Data[a].y);
			if(total == n-1) break;
		}
		if(total == n-1)
			printf("%.4f\n", Data[a].w);
		else
			puts("The empire of Arcturus is ending.");
	}
	return 0;
}
