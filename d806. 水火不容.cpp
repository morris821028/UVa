#include<stdio.h>
struct Axis{
	int t;
}Data[1000000], X[1000000];
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
int Input() {  
    char cha;  
    unsigned int x = 0;  
    while(cha = getchar())  
        if(cha != ' ' && cha != '\n' || cha == EOF) break;  
    if(cha == EOF) return -1; 
    x = cha-48;  
    while(cha = getchar()) {  
        if(cha == ' ' || cha == '\n') break;  
        x = x*10 + cha-48;  
    }
    return x;  
}
main() {
	int N, a;
	while(scanf("%d", &N) == 1) {
		for(a = 0; a < N; a++) Data[a].t = Input();
		MergeSort(0, N-1);
		int max = 0;
		for(a = 0; a < N; a++)
			max = (Data[a].t - max > max) ? Data[a].t - max : max; 
		printf("%d\n", max); 
	}
	return 0; 
}
