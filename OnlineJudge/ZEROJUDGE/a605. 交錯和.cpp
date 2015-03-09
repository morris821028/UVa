#include <stdio.h>
#include <deque>
using namespace std;
struct E {
    long long v;
    int lab;
};
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
    int n, m, i, x;
    deque<E> Q, NQ;
    scanf("%d %d", &n, &m);
    long long ans = -(1LL<<60);
    E p, q;
    for(i = 0; i < n; i++) {
        ReadInt(&x);
        while(Q.front().lab < i-m)
            Q.pop_front();
        while(NQ.front().lab < i-m)
            NQ.pop_front();
        p.v = x, p.lab = i, q.lab = i;
        if(!NQ.empty() && NQ.front().v > 0)
            p.v = NQ.front().v + x;
        if(!Q.empty()) {
            q.v = Q.front().v - x;
            if(q.v > ans)
                ans = q.v;
            while(!NQ.empty() && NQ.back().v <= q.v)
                NQ.pop_back();
            NQ.push_back(q);
        }
        if(p.v > ans)
            ans = p.v;
        while(!Q.empty() && Q.back().v <= p.v)
            Q.pop_back();
        Q.push_back(p);
    }
    printf("%lld\n", ans);
    return 0;
}
