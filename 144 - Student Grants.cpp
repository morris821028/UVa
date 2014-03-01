#include <cstdio>
#include <queue>
using namespace std;

int main() {
    int n, k, i;
    while(scanf("%d %d", &n, &k) == 2) {
        if(n == 0 && k == 0)
            break;
        queue<int> Q;
        for(i = 1; i <= n; i++)
            Q.push(i);
        int cnt[26] = {}, m = 1, tk = 1, tn;
        while(!Q.empty()) {
            tn = Q.front();
            Q.pop();
            if(40-cnt[tn] >= m) {
                cnt[tn] += m;
                m = 0;
            } else {
                m -= 40-cnt[tn];
                cnt[tn] = 40;
            }
            if(m == 0) {
                tk++;
                if(tk > k)
                    tk = 1;
                m += tk;
            }
            if(cnt[tn] < 40)
                Q.push(tn);
            else {
                printf("%3d", tn);
            }
        }
        puts("");
    }
    return 0;
}
