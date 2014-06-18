#include<stdio.h>
#include<stdlib.h>
int Parent[100001], Rank[100001];
int a, N, M;
void MakeSet(int N) {
    for(a=0;a<=N;a++)
		Parent[a] = a, Rank[a] = 1; 
} 
int FindSet(int x) {
    if(x!=Parent[x])
        Parent[x] = FindSet(Parent[x]);
    return Parent[x];
}
void Link(int x, int y) {
    if(Rank[x]>Rank[y])
        	Parent[y] = x, Rank[x] += Rank[y];
    else
        	Parent[x] = y, Rank[y] += Rank[x];
} 
int Union(int x, int y) {
    x = FindSet(x), y = FindSet(y);
    if(x != y) { 
        Link(x, y);
        return 1; 
    } 
    return 0; 
} 
int Input() {  
    char cha;  
    unsigned int x=0;  
    while(cha=getchar())  
        if(cha!=' '&&cha!='\n' || cha==EOF) break;  
    if(cha==-1) return -1; 
    x=cha-48;  
    while(cha=getchar()) {  
        if(cha==' '||cha=='\n') break;  
        x=x*10+cha-48;  
    }  
    return x;  
}
struct Axis{
	int x, y, s;
}Data[400001], X[400001];
void Merge(int, int, int);
void MergeSort(int, int); 
main() {
    int T, a, flag;
    long long Ans;
	while(scanf("%d %d",&N, &M) == 2) { 
        for(a=0;a<M;a++) { 
            Data[a].x = Input(), Data[a].y = Input(), Data[a].s = Input();
            Data[M+a].x = Data[a].x,
			Data[M+a].y = Data[a].y,
			Data[M+a].s = Data[a].s;
        } 
        M *= 2;
		MergeSort(0, M-1), MakeSet(N), Ans = 0, flag = 0;
		
        for(a=0;a<M && flag < N;a++) 
        	if(Union (Data[a].x, Data[a].y) == 1) {
				Ans += Data[a].s, flag ++;
			}
        printf("%lld\n",(flag == N-1)? Ans : -1); 
	}
    return 0; 
}
void MergeSort(int l, int h) {
    if(l < h) {
        int m=(l+h)/2;
        MergeSort(l  ,m);
        MergeSort(m+1,h);
        Merge(l,m,h); 
    }
}
void Merge(int l, int m, int h) {
    int In1=l, In2=m+1;
    int a, b, Top=0;
    while(In1<=m && In2<=h) 
        if((Data[In1].s < Data[In2].s))
             X[Top++]=Data[In1++];
       else  X[Top++]=Data[In2++];
    while(In1<=m)   X[Top++]=Data[In1++];
    while(In2<=h)   X[Top++]=Data[In2++];
    for(a=0,b=l;a<Top;a++,b++) 
        Data[b]=X[a];
} 
