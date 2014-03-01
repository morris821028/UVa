#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int a[100000], n, m, nm;
int test(int k) {
    static int i, j, cnt;
    for(i = 1, j = 0; i <= n; i++) {
        cnt = 0;
        while(j < m && cnt < nm && a[j]-k <= i && i <= a[j]+k) {
            cnt++, j++;
        }
        if(cnt != nm)   return 0;
    }
    return 1;
}
int main() {
    int i;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < m; i++)
            scanf("%d", &a[i]);
        sort(a, a+m);
        nm = m/n;
        int l = 0, r = n/2;
        while(l < r) {
            int m = (l+r)/2;
            if(test(m))
                r = m;
            else
                l = m+1;
        }
        printf("%d\n", r);
    }
    return 0;
}
