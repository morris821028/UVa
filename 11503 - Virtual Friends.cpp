#include <stdio.h>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
int r[100005], p[100005];
void init(int n) {
    for(int i = 0; i <= n; i++)
        r[i] = 1, p[i] = i;
}
int findp(int x) {
    return p[x] == x ? x : (p[x]=findp(p[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x != y) {
        if(r[x] > r[y]) {
            r[x] += r[y], p[y] = x;
            return r[x];
        }
        r[y] += r[x], p[x] = y;
        return r[y];
    }
    return r[x];
}
int main() {
    int t, n, tx, ty;
    char x[30], y[30];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        init(min(2*n, 100000));
        map<string, int> R;
        int size = 0;
        while(n--) {
            scanf("%s %s", &x, &y);
            tx = R[x];
            if(tx == 0)
                R[x] = ++size, tx = size;
            ty = R[y];
            if(ty == 0)
                R[y] = ++size, ty = size;
            printf("%d\n", joint(tx, ty));
        }
    }
    return 0;
}
