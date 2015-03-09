#include <cstdio>
#include <map>
#include <queue>
#include <vector>
#define maxN 100005
using namespace std;
struct ele{
    int a, b;
    ele (int x, int y) {
        a = x;
        b = y;
    }
};
struct cmp {
    bool operator() (ele x, ele y) {
        return x.b < y.b;
    }
};
vector<int> son[maxN];
vector<int> lk[maxN];
map<long long, int> mark, build;
int p[maxN], leaf[maxN];
priority_queue<ele, vector<ele>, cmp> pQ;
void arrange(int x, int pp) {
    p[x] = pp;
    for(vector<int>::iterator it = lk[x].begin();
        it != lk[x].end(); it++) {
        if(*it != pp) {
            son[x].push_back(*it);
            arrange(*it, x);
        }
    }
}
int dfs(int x) {
    int dp = 0, tmp;
    for(vector<int>::iterator it = son[x].begin();
        it != son[x].end(); it++) {
        tmp = dfs(*it);
        ele tt(x, tmp);
        build[(long long)x*maxN + tmp]++;
        pQ.push(tt);
        if(tmp > dp) {
            dp = tmp;
        }
    }
    dp++;
    return dp;
}
int main() {
    int n, m, x, y, i;
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 1; i <= n; i++)
            son[i].clear(), lk[i].clear(), leaf[i] = 0;
        for(i = 1; i < n; i++) {
            scanf("%d %d", &x, &y);
            lk[x].push_back(y);
            lk[y].push_back(x);
            leaf[x]++, leaf[y]++;
        }
        arrange(1, 0);
        mark.clear();
        build.clear();
        dfs(1);
        ele tmp(0, 0);
        int ans = 0;
        while(!pQ.empty() && m) {
            if(mark.size() + build.size() > 1048576)
                while(1);
            tmp = pQ.top();
            pQ.pop();
            long long state = (long long)tmp.a*maxN + tmp.b;
            if(mark[state] != 0) {
                mark[state]--;
            } else {
                ans += tmp.b;
                m--;
                while(tmp.b != 1) {
                    tmp.b--;
                    for(vector<int>::iterator it = son[tmp.a].begin();
                        it != son[tmp.a].end(); it++) {
                        long long state2 = (long long)(*it)*maxN + tmp.b;
                        if(build[state2] != 0) {
                            build[state2]--;
                            mark[state2]++;
                            tmp.a = *it;
                            break;
                        }
                    }
                }
            }
        }
        while(!pQ.empty())
            pQ.pop();
        printf("%d\n", ans);
    }
    return 0;
}
/*
8 3
1 3
1 2
2 4
2 5
4 6
4 7
5 8
8 2
1 2
2 3
2 4
3 5
3 6
4 7
5 8
*/
