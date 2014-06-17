#include <stdio.h>
#include <vector>
using namespace std;
int main() {
    int n, w, a, b, c, i;
    while(scanf("%d %d", &n, &w) == 2) {
        int m = n*(n-1)/2;
        vector<int> g1[501], g2[501], b1[501], b2[501];
        int indeg1[501] = {}, indeg2[501] = {};
        while(m--) {
            scanf("%d %d %d", &a, &b, &c);
            if(c == 0) {
                g1[b].push_back(a);/*b->a*/
                b1[a].push_back(b);
                indeg1[a]++;
            } else {
                g2[a].push_back(b);/*a->b*/
                b2[b].push_back(a);
                indeg2[b]++;
            }
        }
        int flag = 1, used1[501] = {}, ac1[501] = {};
        do {
            flag = 0;
            for(i = 1; i <= n; i++) {
                if(indeg1[i] <= 0 && used1[i] == 0) {
                    used1[i] = 1;
                    for(vector<int>::iterator it = b1[i].begin();
                        it != b1[i].end(); it++) {
                            ac1[i] = ac1[i] > ac1[*it] ? ac1[i] : ac1[*it];
                    }
                    ac1[i]++;
                    for(vector<int>::iterator it = g1[i].begin();
                        it != g1[i].end(); it++) {
                            indeg1[*it]--;
                    }
                    flag = 1;
                }
            }
        } while(flag);
        int used2[501] = {}, ac2[501] = {};
        do {
            flag = 0;
            for(i = 1; i <= n; i++) {
                if(indeg2[i] <= 0 && used2[i] == 0) {
                    used2[i] = 1;
                    for(vector<int>::iterator it = b2[i].begin();
                        it != b2[i].end(); it++) {
                            ac2[i] = ac2[i] > ac2[*it] ? ac2[i] : ac2[*it];
                    }
                    ac2[i]++;
                    for(vector<int>::iterator it = g2[i].begin();
                        it != g2[i].end(); it++) {
                            indeg2[*it]--;
                    }
                    flag = 1;
                }
            }
        } while(flag);
        int R = 0, L = 0;
        for(i = 1; i <= n; i++) {
            R = R > ac1[i] ? R : ac1[i];
            L = L > ac2[i] ? L : ac2[i];
        }
        printf("%d\n", R*L*w*w);
    }
    return 0;
}
