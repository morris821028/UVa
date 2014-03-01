#include<stdio.h>
struct Axis{
	int t;
}Data[1001], X[1001];
void Merge(int l, int m, int h) {
    int In1=l, In2=m+1;
    int a, b, Top=0;
    while(In1<=m && In2<=h) 
        if((Data[In1].t < Data[In2].t))
             X[Top++]=Data[In1++];
       else  X[Top++]=Data[In2++];
    while(In1<=m)   X[Top++]=Data[In1++];
    while(In2<=h)   X[Top++]=Data[In2++];
    for(a=0,b=l;a<Top;a++,b++) 
        Data[b]=X[a];
} 
void MergeSort(int l, int h) {
    if(l < h) {
        int m=(l+h)/2;
        MergeSort(l  ,m);
        MergeSort(m+1,h);
        Merge(l,m,h); 
    }
}

main() {
	int n, a;
	while(scanf("%d", &n) == 1) {
		for(a = 0; a < n; a++)
			scanf("%d", &Data[a].t);
		MergeSort(0, n-1);
		for(a = 0; a < n; a++)
			printf("%d ", Data[a].t);
		puts("");
	}
	return 0;
}
