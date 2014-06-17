#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
bool checkBipartite(int V, vector<int> map[], bool color[], bool used[], int st) {
    queue<int> Q;
    Q.push(st);
    int tn;
    color[st] = true, used[st] = true;
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        for(vector<int>::iterator i = map[tn].begin(); i != map[tn].end(); i++) {
            if(used[*i] == false) {
                used[*i] = true;
                color[*i] = !color[tn];
                Q.push(*i);
            } else {
                if(color[*i] == color[tn])
                    return false;
            }
        }
    }
    return true;
}
int main() {
    int V, x, y;
    vector<int> map[301];
    while(scanf("%d", &V) == 1 && V) {
        for(int i = 0; i <= V; i++)
            map[i].clear();
        while(scanf("%d %d", &x, &y) == 2) {
            if(x == 0 && y == 0)
                break;
            map[x].push_back(y);
            map[y].push_back(x);
        }
        bool color[V+1], used[V+1], ans = true;
        memset(color, 0, sizeof(color));
        memset(used, 0, sizeof(used));
        for(int i = 1; i <= V; i++) {
            if(used[i] == false) {
                ans &= checkBipartite(V, map, color, used, i);
            }
        }
        if(ans == true)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
