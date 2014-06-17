#include <stdio.h>
#include <map>
using namespace std;

int main() {
    int t, n, m, i, j;
    char c, s[1024];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        while(getchar() != '\n');
        map<int, int> g[128];
        while(n--) {
            scanf("%c->%s", &c, s);
            while(getchar() != '\n');
            for(i = 0; s[i]; i++)
                g[c][s[i]]++;
        }
        scanf("%d", &m);
        while(m--) {
            scanf("%s %c %d", s, &c, &n);
            unsigned long long cnt[128] = {}, tmp[128] = {}, num, flag;
            for(i = 0; s[i]; i++)
                cnt[s[i]]++;
            while(n--) {
                for(i = 33; i <= 126; i++) {
                    num = cnt[i], flag = 1;
                    for(map<int, int>::iterator it = g[i].begin();
                        it != g[i].end(); it++) {
                        tmp[it->first] += num * it->second, flag = 0;
                    }
                    tmp[i] += num * flag;
                }
                for(i = 33; i <= 126; i++)
                    cnt[i] = tmp[i], tmp[i] = 0;
            }
            printf("%llu\n", cnt[c]);
        }
    }
    return 0;
}
