#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
struct Pt {
    long long x, y;
    Pt(long long a, long long b):x(a), y(b){}
    Pt():x(0), y(0){}
#define eps 1e-8
    bool operator<(const Pt &a) const {
        if(x != a.x)
            return x < a.x;
        return y < a.y;
    }
};
Pt D[10005];
vector<pair<int, double> > g[10005];
double dis[10005];
int used[10005];
void spfa(double d, int st, int ed, int n) {
    int i, tn, y;
    double v;
    for(i = 0; i < n; i++) {
        dis[i] = d+514;
        used[i] = 0;
    }
    queue<int> Q;
    Q.push(st);
    dis[st] = 0;
    while(!Q.empty()) {
        tn = Q.front(), Q.pop();
        used[tn] = 0;
        for(vector<pair<int, double> >::iterator it = g[tn].begin();
            it != g[tn].end(); it++) {
            y = it->first, v = it->second;
            if(dis[y] > dis[tn] + v && dis[tn]+v <= d) {
                dis[y] = dis[tn]+v;
                if(used[y] == 0) {
                    Q.push(y);
                    used[y] = 1;
                }
            }
        }
    }
    if(dis[ed] <= d)
        puts("I am lucky!");
    else
        puts("Boom!");

}
int main() {
    int w, h, n;
    int i, j, k;
    long long x, y, a, b;
    double d;
    while(scanf("%d %d", &w, &h) == 2) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%lld.%lld %lld.%lld", &x, &y, &a, &b);
            D[i] = Pt(x*100+y, a*100+b);
        }
        D[n++] = Pt(0, 0);
        D[n++] = Pt(w*100, h*100);
        sort(D, D+n);
        for(i = 0; i < n; i++)
            g[i].clear();
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                if(D[j].x-D[i].x > 150)
                    break;
                if((D[j].x-D[i].x)*(D[j].x-D[i].x)+
                   (D[j].y-D[i].y)*(D[j].y-D[i].y) <= 150*150) {
                   g[i].push_back(make_pair(j, sqrt((D[j].x-D[i].x)*(D[j].x-D[i].x)+
                   (D[j].y-D[i].y)*(D[j].y-D[i].y))/100));
                   g[j].push_back(make_pair(i, sqrt((D[j].x-D[i].x)*(D[j].x-D[i].x)+
                   (D[j].y-D[i].y)*(D[j].y-D[i].y))/100));
                }
            }
        }
        scanf("%lf", &d);
        spfa(d, 0, n-1, n);
    }
    return 0;
}
