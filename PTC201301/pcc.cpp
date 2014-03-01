#include <stdio.h>
#include <iostream>
#include <queue>
using namespace std;
int st[1<<20];
int main() {
    int n, k, i, j;
    int t, hh, mm, ss;
    scanf("%d", &t);
    while(t--) {
        cin >> n >> hh >> mm >> ss;
        int take = hh;
        mm = mm*mm*mm;
        ss = ss*ss*ss;
        int M;
        for(M = 1; M < n+1; M <<= 1);
        for(i = 2*M-1; i > 0; i--) {
            if(i >= M)
                st[i] = 1;
            else
                st[i] = st[i<<1]+st[i<<1|1];
        }
        int m, last, prev = 0, s;
        for(i = 1; i <= n; i++) {
            m = (take+prev)%(n-i+1);
            if(m == 0)
                m = n-i+1;
            prev = m-1;
            for(s = 1; s < M;) {
                if(st[s<<1] < m)
                    m -= st[s<<1], s = s<<1|1;
                else
                    s = s<<1;
            }
            last = s-M+1;
            take = last;
            if(i != n) {
                if(take%2) take = (mm)%(n-i)+1;
                else take = (ss)%(n-i)+1;
            }
            while(s) {
                st[s] --;
                s >>= 1;
            }
        }
        printf("%d\n", last);
    }
    return 0;
}
