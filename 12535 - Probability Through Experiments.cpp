#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
int x[20005];
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, r, i, j, a, b;
    int cases = 0;
    while(scanf("%d %d", &n, &r) == 2) {
        if(n == 0)  break;
        for(i = 0; i < n; i++) {
            ReadInt(&a);
            ReadInt(&b);
            x[i] = a*1000+b;
        }
        sort(x, x+n);
        long long tot = 0, t1, t2, normal = 0, ans;
        ans = (long long)n*(n-1)*(n-2)/6;
        queue<int> Q;
        for(i = 0, j = 0; i < n; i++) {
            if(x[i] >= 180000)  break;
            while(j < n && x[j] <= x[i]+180000)
                Q.push(x[j]), j++;
            while(!Q.empty() && Q.front() <= x[i])  Q.pop();
            t1 = Q.size();
            t2 = n-1-t1;
            if(j > 0 && x[j-1] == x[i]+180000)
                t1--, normal += t1+t2;
            tot += t1*(t1-1)/2;
            tot += t2*(t2-1)/2;
        }
        for(i = 0; i < n; i++) {
            x[i] += 180000;
            if(x[i] >= 360000)  x[i] -= 360000;
        }
        sort(x, x+n);
        while(!Q.empty())   Q.pop();
        for(i = 0, j = 0; i < n; i++) {
            if(x[i] >= 180000)  break;
            while(j < n && x[j] <= x[i]+180000)
                Q.push(x[j]), j++;
            while(!Q.empty() && Q.front() <= x[i])  Q.pop();
            t1 = Q.size();
            t2 = n-1-t1;
            if(j > 0 && x[j-1] == x[i]+180000)
                t1--, normal += t1+t2;
            tot += t1*(t1-1)/2;
            tot += t2*(t2-1)/2;
        }
        printf("Case %d: %lld\n", ++cases, ans-tot/2-normal/2);
    }
    return 0;
}
/*
3 5
0.000
30.000
180.000
*/
