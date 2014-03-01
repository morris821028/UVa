#include <stdio.h>
#include <queue>
using namespace std;

int main() {
    int t, n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        n = n*100;
        queue<int> L, R;
        int l;
        char s[50];
        while(m--) {
            scanf("%d %s", &l, s);
            if(s[0] == 'l')
                L.push(l);
            else
                R.push(l);
        }
        int flag = 0, res = 0;
        while(!L.empty() || !R.empty()) {
            res++;
            int sum = 0;
            if(flag) { // right
                while(!R.empty() && sum + R.front() <= n)
                    sum += R.front(), R.pop();
            } else {
                while(!L.empty() && sum + L.front() <= n)
                    sum += L.front(), L.pop();
            }
            flag = 1-flag;
        }
        printf("%d\n", res);
    }
    return 0;
}
