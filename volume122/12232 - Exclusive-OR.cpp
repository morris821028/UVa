#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <algorithm>
using namespace std;

int parent[32767], weight[32767], n;
void init(int n) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i, weight[i] = 0;
    }
}

int findp(int x) {
    if (x != parent[x]) {
        int p = parent[x];
        parent[x] = findp(parent[x]);
        weight[x] = weight[x] ^ weight[p];
    }
    return parent[x];
}
int joint(int x, int y, int w) {
    int px, py;
    px = findp(x), py = findp(y);
    if (px == py)
        return (weight[x] ^ weight[y]) == w;
    if (px == n) // virtual point
        swap(px, py);
    parent[px] = py;
    weight[px] = weight[x] ^ weight[y] ^ w;
    return 1;
}
int main() {
    int q, cases = 0;
    int m, x, y, v;
    char cmd[1024], line[1024];
    while (scanf("%d %d", &n, &q) == 2 && n) {
        init(n);
        
        printf("Case %d:\n", ++cases);
        
        int conflict = 0, error = 0;
        for (int i = 0; i < q; i++) {
            scanf("%s", cmd);
            if (cmd[0] == 'I') {
                gets(line);
                if (error)
                    continue;
                if (sscanf(line, "%d %d %d", &x, &y, &v) == 3) {
                    
                } else if (sscanf(line, "%d %d", &x, &v) == 2) {
                    y = n;
                }
                conflict++;
                if (!joint(x, y, v)) {
                    printf("The first %d facts are conflicting.\n", conflict);
                    error = 1;
                }
            } else {
                scanf("%d", &m);
                
                int ret = 0, ok = 1;
                map<int, int> R;
                for (int j = 0; j < m; j++) {
                    scanf("%d", &x);
                    int px = findp(x);
                    ret = ret ^ weight[x];
                    R[px]++;
                }
                if (error)
                    continue;
                for (map<int, int>::iterator it = R.begin(); it != R.end(); it++) {
                    if (it->second % 2) {
                        if (it->first == n)
                            ret = ret ^ weight[it->first];
                        else
                            ok = 0;
                    }
                }
                if (ok)
                    printf("%d\n", ret);
                else
                    puts("I don't know.");
            }
        }
        puts("");
    }
    return 0;
}
/*
 2 6
 I 0 1 3
 Q 1 0
 Q 2 1 0
 I 0 2
 Q 1 1
 Q 1 0
 3 3
 I 0 1 6
 I 0 2 2
 Q 2 1 2
 2 4
 I 0 1 7
 Q 2 0 1
 I 0 1 8
 Q 2 0 1
 0 0
 */