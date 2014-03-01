#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
struct I {
    int x, y, c;
};
struct cmp {
    bool operator() (I a, I b) {
        return a.x > b.x;
    }
};
int main() {
    int n, m, i, j, k, x, y, c;
    while(scanf("%d %d", &n, &m) == 2) {
        if(!n && !m)
            break;
        priority_queue<I, vector<I>, cmp> pQ;
        I II;
        int flag = 0;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &II.x ,&II.y);
            II.c = 0;
            pQ.push(II);
        }
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &II.x ,&II.y, &II.c);
            pQ.push(II);
        }
        int right = 0;
        while(!pQ.empty()) {
            II = pQ.top();
            pQ.pop();
            if(II.x < right) {
                flag = 1;
                break;
            }
            if(II.x >= 1000000)
                break;
            right = II.y;
            if(II.c) {
                II.x += II.c;
                II.y += II.c;
                pQ.push(II);
            }
        }
        puts(flag ? "CONFLICT" : "NO CONFLICT");
    }
    return 0;
}
