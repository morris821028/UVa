#include <stdio.h>
#define maxN 55
int Parent[maxN], Rank[maxN];
void MakeInit(int n) {
    int i;
    for(i = 0; i <= n; i++)
        Parent[i] = i, Rank[i] = 1;
}
int FindParent(int x) {
    if(Parent[x] != x)
        Parent[x] = FindParent(Parent[x]);
    return Parent[x];
}
void PLink(int x, int y) {
    if(Rank[x] > Rank[y]) {
        Rank[x] += Rank[y];
        Parent[y] = x;
    } else {
        Rank[y] += Rank[x];
        Parent[x] = y;
    }
}
int Union(int x, int y) {
    x = FindParent(x), y = FindParent(y);
    if(x != y) {
        PLink(x, y);
        return 1;
    }
    return 0;
}
int main() {
    int n, i, j;
    scanf("%d", &n);
    while(n--) {
        int x, y;
        int map[51][51] = {};
        int node[51] = {};
        MakeInit(50);
        while(scanf("%d %d", &x, &y) == 2) {
            if(x == 0 && y == 0)
                break;
            map[x][y] = 1;
            map[y][x] = 1;
            node[x] = 1;
            node[y] = 1;
            Union(x, y);
        }
        int tn = 0, tm = 0;
        for(i = 0; i <= 50; i++)
            tn += node[i];
        for(i = 0; i <= 50; i++) {
            for(j = 0; j <= 50; j++)
                tm += map[i][j];
        }
        tm /= 2;
        int max = 0;
        for(i = 0; i <= 50; i++)
            max = Rank[i] > max ? Rank[i] : max;
        if(max == tn && tn-1 == tm)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
