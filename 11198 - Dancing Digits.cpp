#include <stdio.h>
#include <map>
#include <queue>
using namespace std;
int isprime(int n) {
    int i;
    for(i = 2; i < n; i++)
        if(n%i == 0)
            return 0;
    return 1;
}
int main() {
    int n[8], sign[9], cases = 0;
    int i, j, k, isp[9][9];
    for(i = 1; i <= 8; i++)
        for(j = 1; j <= 8; j++)
            isp[i][j] = isprime(i+j);
    while(scanf("%d", &n[0]), n[0]) {
        if(n[0] < 0)
            n[0] *= -1, sign[n[0]] = 1;
        else    sign[n[0]] = 0;
        int tmp = n[0];
        for(i = 1; i < 8; i++) {
            scanf("%d", &n[i]);
            if(n[i] < 0)
                n[i] *= -1, sign[n[i]] = 1;
            else    sign[n[i]] = 0;
            tmp = tmp*10 + n[i];
        }
        queue<int> Q;
        map<int, int> G;
        map<int, int>::iterator it;
        Q.push(tmp);
        G[tmp] = 0;
        int a[8], state, step;
        while(!Q.empty()) {
            tmp = Q.front();
            Q.pop();
            if(tmp == 12345678) {
                tmp = -1;
                break;
            }
            step = G[tmp];
            for(i = 7; i >= 0; i--)
                a[i] = tmp%10, tmp /= 10;
            for(i = 0; i < 8; i++) {
                for(j = 0; j < 8; j++) {
                    if(i == j)  continue;
                    if(sign[a[i]] != sign[a[j]] && isp[a[i]][a[j]]) {
                        /*left*/
                        for(k = 0, state = 0; k < j; k++) {
                            if(k == i)  continue;
                            state = state*10 + a[k];
                        }
                        state = state*10 + a[i], state = state*10 + a[j];
                        for(k = j+1; k < 8; k++) {
                            if(k == i)  continue;
                            state = state*10 + a[k];
                        }
                        if(G.find(state) == G.end()) {
                            G[state] = step+1;
                            Q.push(state);
                        }
                        /*right*/
                        for(k = 0, state = 0; k < j; k++) {
                            if(k == i)  continue;
                            state = state*10 + a[k];
                        }
                        state = state*10 + a[j], state = state*10 + a[i];
                        for(k = j+1; k < 8; k++) {
                            if(k == i)  continue;
                            state = state*10 + a[k];
                        }
                        if(G.find(state) == G.end()) {
                            G[state] = step+1;
                            Q.push(state);
                        }
                    }
                }
            }
        }
        printf("Case %d: ", ++cases);
        if(tmp == -1)
            printf("%d\n", G[12345678]);
        else
            puts("-1");
    }
    return 0;
}
