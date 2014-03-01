#include <stdio.h>
#include <set>
#include <vector>
using namespace std;
vector<int> g[10000];
int main() {
    int n, m, size, t;
    int i, j, k, x, y;
    char mp[105][105];
    int nd[105][105];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            scanf("%s", &mp[i]);
        size = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(mp[i][j] == '.') {
                    nd[i][j] = ++size;
                    g[size].clear();
                }
            }
        }
        int dir[4][2] = {{-1,-1},{-1,1},{0,1},{0,-1}};
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(mp[i][j] == 'x') continue;
                for(k = 0; k < 4; k++) {
                    x = i+dir[k][0];
                    y = j+dir[k][1];
                    if(x < 0 || y < 0 || x >= n || y >= m)
                        continue;
                    if(mp[x][y] == 'x') continue;
                    g[nd[i][j]].push_back(nd[x][y]);
                    g[nd[x][y]].push_back(nd[i][j]);
                }
            }
        }
        set<int> VN1, VN2;
        bool ev1, ev2;
        for(i = 1; i <= size; i++) {
            ev1 = VN1.find(i) != VN1.end();
            ev2 = VN2.find(i) != VN2.end();
            if(ev1 == true && ev2 == true)
                continue;
            if(ev2 == false) {
                VN1.insert(i);
                for(vector<int>::iterator it = g[i].begin();
                    it != g[i].end(); it++)
                    VN2.insert(*it);
            } else {
                VN2.insert(i);
                for(vector<int>::iterator it = g[i].begin();
                    it != g[i].end(); it++)
                    VN1.insert(*it);
            }
        }
        int A = 0, B = 0;
        for(set<int>::iterator it = VN1.begin();
            it != VN1.end(); it++) {
            if(VN2.find(*it) == VN2.end())
                A++;
        }
        for(set<int>::iterator it = VN2.begin();
            it != VN2.end(); it++) {
            if(VN1.find(*it) == VN1.end())
                B++;
        }
        if(A > B) A = B;
        printf("%d\n", size - A);
    }
    return 0;
}
