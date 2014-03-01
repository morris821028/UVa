#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

int main() {
    int n, m, cases = 0, i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        int g[105][105] = {};
        vector<string> Rv;
        map<string, int> R;
        string x, y;
        for(i = 0; i < 105; i++)
            for(j = 0; j < 105; j++)
                g[i][j] = 0;
        int idx = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &m);
            int pre = idx;
            for(j = 0; j < m; j++) {
                cin >> x;
                R[x] = idx, Rv.push_back(x);
                idx++;
            }
            for(j = pre; j < idx-1; j++)
                g[j][j+1] = 1;
        }
        scanf("%d", &m);
        while(m--) {
            cin >> x >> y;
            g[R[x]][R[y]] = 1;
        }
        for(k = 0; k < idx; k++)
            for(i = 0; i < idx; i++)
                for(j = 0; j < idx; j++)
                    g[i][j] |= g[i][k]&g[k][j];

        string res = "";
        int cnt = 0;
        for(i = 0; i < idx; i++)
            for(j = i+1; j < idx; j++)
                if(g[i][j] == 0 && g[j][i] == 0) {
                    cnt++;
                    if(cnt <= 2) {
                        res = res+"("+Rv[i]+","+Rv[j]+") ";
                    }
                }
        if(cnt) {
            printf("Case %d, %d concurrent events:\n", ++cases, cnt);
            cout << res << endl;
        } else
            printf("Case %d, no concurrent events.\n", ++cases);
    }
    return 0;
}
