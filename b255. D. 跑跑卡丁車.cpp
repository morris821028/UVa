#include<stdio.h>
struct Axis{
	double t;
	int index;
}Data[100001], X[100001];
void Merge(int l, int m, int h) {
    int In1=l, In2=m+1;
    int a, b, Top=0;
    while(In1<=m && In2<=h) 
        if(Data[In1].t <= Data[In2].t)
             X[Top++] = Data[In1++];
       else  X[Top++] = Data[In2++];
    while(In1<=m)   X[Top++] = Data[In1++];
    while(In2<=h)   X[Top++] = Data[In2++];
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
char name[100000][50];
double time[100000];
main() {
	int n, H, M, a;
	double S;
	while(scanf("%d", &n) == 1 && n) {
		for(a = 0; a < n; a++) {
			scanf("%s %d:%d:%lf", name[a], &H, &M, &S);
			Data[a].t = H*3600.0 + M*60.0 + S, Data[a].index = a;
			time[a] = Data[a].t;
		}
		MergeSort(0, n-1);
		int n2 = n/3-1;
		puts("LIST START");
		for(a = 0; a < n; a++)
			if(time[a] <= Data[n2].t)
				puts(name[a]);
		puts("LIST END");
	}
	return 0;
}
