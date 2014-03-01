#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
struct ele {
    int v, col, row;
};
struct cmp {
    bool operator() (ele a, ele b) {
        if(a.col != b.col)
            return a.col > b.col;
        return a.row > b.row;
    }
};
priority_queue<ele, vector<ele>, cmp> pQ;
int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) == 2) {
        ele p[10000];
        int i, j, k;
        for(i = 0; i < n; i++) {
            scanf("%d", &k);
            for(j = 0; j < k; j++)
                scanf("%d", &p[j].col);
            for(j = 0; j < k; j++)
                scanf("%d", &p[j].v);
            for(j = 0; j < k; j++)
                p[j].row = i+1, pQ.push(p[j]);

        }
        printf("%d %d\n", m, n);
        for(i = 1; i <= m; i++) {
            int idx = 0;
            while(!pQ.empty() && pQ.top().col == i) {
                p[idx++] = pQ.top();
                pQ.pop();
            }
            printf("%d", idx);
            for(j = 0; j < idx; j++)
                printf(" %d", p[j].row);
            puts("");
            for(j = 0; j < idx; j++) {
                if(j)   putchar(' ');
                printf("%d", p[j].v);
            }
            puts("");
        }
    }
    return 0;
}
