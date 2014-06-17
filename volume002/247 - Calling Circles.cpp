#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

int main() {
    int n, m, cases = 0;
    while(cin >> n >> m) {
        if(!n && !m)
            break;
        if(cases)
            puts("");
        printf("Calling circles for data set %d:\n", ++cases);
        map<string, int> r;
        int size = 0, graph[26][26] = {}, i, j, k;
        int x, y, used[26] = {};
        string name[26], a, b;
        while(m--) {
            cin >> a >> b;
            x = r[a];
            if(x == 0)
                r[a] = ++size, x = size, name[size] = a;
            y = r[b];
            if(y == 0)
                r[b] = ++size, y = size, name[size] = b;
            graph[x][y] = 1;
        }
        for(i = 1; i <= size; i++)
            graph[i][i] = 1;
        for(k = 1; k <= size; k++) {
            for(i = 1; i <= size; i++) {
                for(j = 1; j <= size; j++) {
                    if(graph[i][k] == 1 && graph[k][j] == 1)
                        graph[i][j] = 1;
                }
            }
        }
        for(i = 1; i <= size; i++) {
            if(!used[i]) {
                int cnt = 0;
                for(j = 1; j <= size; j++) {
                    if((!used[j]) && graph[i][j] && graph[j][i]) {
                        used[j] = 1;
                        used[i] = 1;
                        if(cnt)
                            printf(", ");
                        printf("%s", name[j].c_str());
                        cnt++;
                    }
                }
                puts("");
            }
        }
    }
    return 0;
}
