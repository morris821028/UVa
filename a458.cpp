#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
#define LL long long
#define oo 0xffffffffffLL
#define maxN 200001
using namespace std;

struct arc {
    LL to, w;
};
struct ele {
    LL nd, w;
    ele(LL x, LL y): nd(x), w(y) {}
};
typedef vector<arc>::iterator it;
struct cmp {
    bool operator()(ele a, ele b) {
        return a.w > b.w;
    }
};
struct seg {
    LL s, e, v;
    it p;
};
struct cmp2 {
    bool operator()(seg a, seg b) {
        return a.e > b.e;
    }
};
bool cmps(seg a, seg b) {
    return a.s < b.s;
}
bool cmpw(seg a, seg b) {
    return a.p->w > b.p->w;
}
vector<arc> g[maxN];
LL dis[maxN], cdis[maxN], used[maxN];
seg SEG[maxN];

priority_queue<ele, vector<ele>, cmp> pQ;
priority_queue<seg, vector<seg>, cmp2> pQ2;

LL dijkstra(int, int, int);

LL cntA = 0, cntB = 0;
void sol(int st, int ed, int n) {
    int v, m = 0, i;
    queue<int> Q;
    Q.push(ed);
    for(i = 1; i <= n; i++)
        used[i] = 0, cdis[i] = dis[i];
    while(!Q.empty()) {
        v = Q.front();
        Q.pop();
        for(it i = g[v].begin();
            i != g[v].end(); i++) {
            if(dis[i->to] == dis[v] - i->w) {
                SEG[m].s = dis[i->to];
                SEG[m].e = dis[v];
                SEG[m].v = v;
                SEG[m++].p = i;
                if(used[i->to] == 0) {
                    used[i->to] = 1;
                    Q.push(i->to);
                }
            }
        }
    }
    sort(SEG, SEG+m, cmps);
    LL ans = 0, odis = dis[ed], tmp;
    it ip;
    int runtime = 0, tj = 0;
    for(i = 0; i < m; i++) {
        while(!pQ2.empty() && SEG[i].s >= pQ2.top().e)
            pQ2.pop();
        tmp = SEG[i].s;
        while(i < m && SEG[i].s == tmp)
            pQ2.push(SEG[i]), i++;
        i--;
        if(pQ2.size() == 1) {
            SEG[tj++] = SEG[i];
            //printf("%lld %lld\n", SEG[i].s, SEG[i].e);
        }
    }
    while(!pQ2.empty()) pQ2.pop();
    sort(SEG, SEG+tj, cmpw);
    for(i = 0; i < tj; i++) {
        //printf("%lld %lld\n", SEG[i].s, SEG[i].e);
        if(SEG[i].p->w <= ans)
            continue;
        //if(runtime > 3000000)   break;
        for(ip = g[SEG[i].p->to].begin();
            ip != g[SEG[i].p->to].end(); ip++) {
            if(ip->to == SEG[i].v)
                break;
        }
        runtime += n;
        for(int j = 1; j <= n; j++) {
            if(cdis[j] <= SEG[i].s)
                pQ.push(ele(j, cdis[j]));
            else
                dis[j] = cdis[j]+ip->w;
            used[j] = 0;
        }
        SEG[i].p->w *= 2;
        ip->w *= 2;
        tmp = dijkstra(st, ed, n);
        if(tmp - odis >= ans)
            ans = tmp - odis;
        if(ans == ip->w/2)
            break;
        ip->w /= 2;
        SEG[i].p->w /= 2;
        i += rand()%2;
    }
    printf("%lld\n", ans);
}
LL dijkstra(int st, int ed, int n) {
    int i;
    ele tn(0,0);
    while(!pQ.empty()) {
        tn = pQ.top();
        pQ.pop();
        if(used[tn.nd] || dis[tn.nd] >= dis[ed]) continue;
        used[tn.nd] = 1;
        for(it i = g[tn.nd].begin();
            i != g[tn.nd].end(); i++) {
            if(dis[i->to] > dis[tn.nd] + i->w) {
                dis[i->to] = dis[tn.nd] + i->w;
                pQ.push(ele(i->to, dis[i->to]));
            }
        }
    }
    return dis[ed];
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
LL ReadLong(LL *x) {
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
    int n, m, i, a, b, st, ed;
    LL w;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 1; i <= n; i++) g[i].clear();
        arc e;
        while(m--) {
            ReadInt(&a), ReadInt(&b);
            ReadLong(&w);
            //scanf("%d %d %lld", &a, &b, &w);
            e.to = b, e.w = w;
            g[a].push_back(e);
            e.to = a;
            g[b].push_back(e);
        }
        scanf("%d %d", &st, &ed);
        for(i = 1; i <= n; i++)
            dis[i] = oo, used[i] = 0;
        dis[st] = 0;
        pQ.push(ele(st, 0));
        dijkstra(st, ed, n);
        sol(st, ed, n);
    }
    return 0;
}
/*
10 9
4 10 12
8 4 24
4 6 10
4 2 11
3 6 18
5 10 11
5 7 24
1 7 5
1 9 17

5 6
1 2 5
2 3 3
3 5 2
2 4 1
4 5 4
1 5 10
1 5
*/
