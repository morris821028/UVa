#include <stdio.h>
#include <queue>
using namespace std;
struct Point {
    int x, y, d;
};
int main() {
    int t, D, K;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &D, &K);
        Point st, ed;
        st.x = 0, st.y = 0, st.d = 1;
        queue<Point> Q;
        Q.push(st);
        int ans = 0;
        while(!Q.empty()) {
            st = Q.front();
            Q.pop();
            if(st.y == K) {
                ans++;
                printf("%d %d\n", st.x, st.y);
            }
            else {
                if(st.d == D) {
                    printf("%d %d\n", st.x, st.y);
                    ans++;
                }
                else {
                ed.x = st.x+1, ed.y = st.y, ed.d = st.d+1;
                Q.push(ed);
                ed.x = st.x, ed.y = st.y+1, ed.d = st.d+1;
                Q.push(ed);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
