#include <cstdio>
#include <algorithm>
#define oo 0xfffffff
using namespace std;
const int SIZE = 500;
int A[SIZE*SIZE];
int p[SIZE][SIZE];
int getIdx(int pd, int v) {
    static int l, r, m;
    l = 0, r = SIZE-1;
    while(l <= r) {
        m = (l+r)>>1;
        if(p[pd][m] == v)
            return m;
        if(p[pd][m] < v)
            l = m+1;
        else
            r = m-1;
    }
    return -1;
}
int getRank(int x, int y, int k) {
    int s = 0, l, r, m;
    while(x%SIZE && x <= y) {
        if(A[x] <= k)    s++;
        x++;
    }
    while((y+1)%SIZE && x <= y) {
        if(A[y] <= k)    s++;
        y--;
    }
    if(x > y)   return s;
    x /= SIZE, y /= SIZE;
    while(x <= y) {
        l = 0, r = SIZE-1, m;
        while(l < r) {
            m = (l+r+1)>>1;
            if(p[x][m] <= k)
                l = m;
            else
                r = m-1;
        }
        if(p[x][l] > k) l--;
        s += l+1;
        x++;
    }
    return s;
}
int main() {
    int n, q, i, j, k, d, idx;
    char cmd[3];
    while(scanf("%d %d", &n, &q) == 2) {
        for(i = 0; i < SIZE; i++)
            p[(n-1)/SIZE][i] = oo;
        for(i = 0; i < n; i++)
            scanf("%d", A+i), p[i/SIZE][i%SIZE] = A[i];
        for(i = (n-1)/SIZE; i >= 0; i--)
            sort(p[i], p[i]+SIZE);
        while(q--) {
            scanf("%d %d %d", &i, &j, &k), i--, j--;
            int l, r = 1000000000, m;
            l = -r;
            while(l < r) {
                m = (l+r+1)>>1;
                if(getRank(i, j, m) >= k)
                    r = m-1;
                else
                    l = m;
            }
            printf("%d\n", r+1);
        }
    }
    return 0;
}
