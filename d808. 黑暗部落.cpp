#include<stdio.h>
int Parent[1000001], Rank[1000001];
int a, Ans;
void MakeSet(int N) {
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
        Link(x, y), Ans--;
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
	int N, x, a;
	while(scanf("%d", &N) == 1) {
		MakeSet (N); 
		for(a = 1, Ans = N; a <= N; a++) 
			x = Input(), Union(a, x); 
		int max = 0;
		for(a = 1; a <= N; a++)
			if(Rank[a] > max) max = Rank[a]; 
		printf("%d %d\n", Ans, max); 
	}
	return 0; 
}
