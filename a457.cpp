#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
struct D {
    int s, r;
};
bool cmp(D a, D b) {
    if(a.s != b.s)  return a.s > b.s;
    return a.r > b.r;
}
int n, i, j;
unsigned res = 0;
int C[100005] = {}, x, y;
map<int, int> R;
int main() {
    scanf("%d %*d", &n);
    D d[n];
    for(i = 0; i < n; i++)
        scanf("%d", &d[i].s);
    for(i = 0; i < n; i++)
        scanf("%d", &d[i].r), R[d[i].r] = 1;
    sort(d, d+n, cmp);
    i = 1;
    for(map<int, int>::iterator it = R.begin();
        it != R.end(); it++)
        it->second = ++i;
    int size = i;
    for(i = 0; i < n; i++) {
        y = x = R[d[i].r]-1;
        while(y)
            res += C[y], y -= y&(-y);
        x++;
        while(x <= size)
            C[x]++, x += x&(-x);

    }
    printf("%u\n", res);
    return 0;
}
