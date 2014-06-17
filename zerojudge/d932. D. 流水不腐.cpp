#include<stdio.h>
#include<stdlib.h>
struct Axis{
	int t, v;
}Data[1001], X[1001];
int Ans;
void Merge(int l, int m, int h) {
    int In1 = l, In2 = m+1;
    int a, b, Top=0, D = 0;
    while(In1 <= m && In2 <= h) 
        if(Data[In1].t < Data[In2].t)
             Ans += Data[In1].v*D, X[Top++] = Data[In1++];
       else  Ans += Data[In2].v*(In2 - (Top+l)), X[Top++] = Data[In2++], D++;
    while(In1 <= m)   Ans += Data[In1].v*D, X[Top++] = Data[In1++];
    while(In2 <= h)   Ans += Data[In2].v*(In2 - (Top+l)), X[Top++] = Data[In2++];
    for(a = 0, b = l; a < Top; a++, b++) 
        Data[b] = X[a];
} 
void MergeSort(int l, int h) {
    if(l < h) {
        int m = (l+h)/2;
        MergeSort(l  , m);
        MergeSort(m+1, h);
        Merge(l, m, h); 
    }
}
main() {
	int T, n, a;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(a = 0; a < n; a++)	scanf("%d", &Data[a].t);
		for(a = 0; a < n; a++)	scanf("%d", &Data[a].v);
		Ans = 0, MergeSort(0, n-1);
		printf("%d\n", Ans);
	}
	return 0;
}
