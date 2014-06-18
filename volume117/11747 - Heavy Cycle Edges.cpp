#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;
typedef struct {
    int i, j, v;
} E;
E D[25005];
vector<int> g[1005];
int cmp(const void *i, const void *j) {
    static E *a, *b;
    a = (E *)i, b = (E *)j;
    return b->v - a->v;
}
int main() {
    int n, m, i, j;
    int x, y, v;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)  break;
        for(i = 0; i < n; i++)
            g[i].clear();
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &D[i].i, &D[i].j, &D[i].v);
            g[D[i].i].push_back(D[i].j);
            g[D[i].j].push_back(D[i].i);
        }
        qsort(D, m, sizeof(E), cmp);
        int tn;
        vector<int> buf;
        char used[n];
        for(i = 0; i < m; i++) {
            for(j = 0; j < n; j++)  used[j] = 0;
            used[D[i].i] = 1;
            queue<int> Q;
            Q.push(D[i].i);
            while(!Q.empty()) {
                tn = Q.front();
                Q.pop();
                for(j = 0; j < g[tn].size(); j++) {
                    if(tn == D[i].i && g[tn][j] == D[i].j)  continue;
                    if(!used[g[tn][j]]) {
                        used[g[tn][j]] = 1;
                        Q.push(g[tn][j]);
                    }
                }
            }
            if(used[D[i].j]) {
                for(vector<int>::iterator it = g[D[i].i].begin();
                    it != g[D[i].i].end(); ) {
                    if(*it == D[i].j) {
                        it = g[D[i].i].erase(it);
                        break;
                    } else {
                        it++;
                    }
                }
                for(vector<int>::iterator it = g[D[i].j].begin();
                    it != g[D[i].j].end(); ) {
                    if(*it == D[i].i) {
                        it = g[D[i].j].erase(it);
                        break;
                    } else {
                        it++;
                    }
                }
                buf.push_back(D[i].v);
            }
        }
        if(buf.size()) {
            for(i = buf.size()-1; i >= 0; i--) {
                printf("%d", buf[i]);
                if(i)  putchar(' ');
            }
            puts("");
        } else
            puts("forest");
    }
    return 0;
}
