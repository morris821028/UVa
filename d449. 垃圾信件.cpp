#include<stdio.h>
#include<stdlib.h>
int Parent[1010001], Realpt[10001];
short Rank[1010001];
int Ans;
void Init(int n, int m) {
	int a;
	m = m > n ? m : n;
	m += n;
    for(a = 0; a <= m; a++)
        Parent[a] = a, Rank[a] = 1; 
    for(a = 0; a <= n; a++)
    	Realpt[a] = a;
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
int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
main() {
	int n, m, op, vir, a, x, y, px;
	while(ReadInt(&n) != EOF) {
		ReadInt(&m);
		Init(n, m), Ans = n, vir = n+1;
		for(a = 0; a < m; a++) {
			ReadInt(&op);
			if(op == 1) {
				ReadInt(&x), ReadInt(&y);
				Union(Realpt[x], Realpt[y]);
			} else {
				ReadInt(&x);
				px = FindSet(Realpt[x]);
				if(Rank[px] > 1) {
					Ans++;
					Rank[px]--;
					Realpt[x] = vir++;
				}
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
