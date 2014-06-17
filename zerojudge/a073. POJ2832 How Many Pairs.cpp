#include<stdio.h>
int Parent[100001], Rank[100001];
long long Ans = 0;
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
    Ans += (Rank[x]*Rank[y]);
    if(Rank[x] > Rank[y])
        Parent[y] = x, Rank[x] += Rank[y];
    else
        Parent[x] = y, Rank[y] += Rank[x];
} 
void Union(int x, int y) {
    x = FindSet(x), y = FindSet(y);
    if(x != y)
        Link(x, y);
}
typedef struct {
    int x, y, w;
}link;
link Map[200000], X[200000], query[200000];
long long queryAns[200000];
void MergeSort(int, int, link []);
int Input() { 
    char cha; 
    unsigned int x = 0; 
    while(cha = getchar()) 
        if(cha != ' ' && cha != '\n') break; 
    x = cha-48; 
    while(cha = getchar()) { 
        if(cha == ' ' || cha == '\n') break; 
        x = x*10 + cha-48; 
    } 
    return x; 
}
main() {
    int N, M, Q, a;
    while(scanf("%d %d %d", &N, &M, &Q) == 3) {
        MakeSet(N);
        for(a = 0; a < M; a++)
            Map[a].x = Input(), Map[a].y = Input(), Map[a].w = Input();
        for(a = 0; a < Q; a++)
            query[a].w = Input(), query[a].y = a;
        MergeSort(0, M-1, Map);
        MergeSort(0, Q-1, query);
        int index = 0;
        Ans = 0;
        for(a = 0; a < Q; a++) {
            while(index < M && Map[index].w <= query[a].w)
                Union(Map[index].x, Map[index].y), index++;
            queryAns[query[a].y] = Ans;
        }
        for(a = 0; a < Q; a++)
            printf("%lld\n", queryAns[a]);
    }
    return 0;
}
void Merge(int l, int m, int r, link Data[]) {
    int In1 = l, In2 = m+1;
    int a, b, Top = 0;
    while(In1 <= m && In2 <= r)
        if(Data[In1].w <= Data[In2].w)
            X[Top++] = Data[In1++];
        else
            X[Top++] = Data[In2++];
    while(In1 <= m) X[Top++] = Data[In1++];
    while(In2 <= r) X[Top++] = Data[In2++];
    for(a = 0, b = l; a < Top; a++, b++)
        Data[b] = X[a];
}
void MergeSort(int l, int r, link Data[]) {
    if(l < r) {
        int m = (l+r)/2;
        MergeSort(l, m, Data);
        MergeSort(m+1, r, Data);
        Merge(l, m, r, Data);
    }
}
