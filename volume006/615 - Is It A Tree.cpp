#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <queue>
#include <vector>
using namespace std;
struct Arc {
    int to;
};
int main() {
    int i, j, t = 0;
    map<int, int> node;
    while(1) {
        int size = 0, x, y;
        int indeg[100] = {};
        vector<Arc> myLink[100];
        Arc tmp;
        node.clear();
        while(scanf("%d %d", &i, &j) == 2) {
            if(i < 0 && j < 0)  goto End;
            if(!i && !j)    break;
            x = node[i];
            if(!x) {
                ++size;
                node[i] = size;
                x = size;
            }
            y = node[j];
            if(!y) {
                ++size;
                node[j] = size;
                y = size;
            }
            tmp.to = y;
            indeg[y]++;
            myLink[x].push_back(tmp);
        }
        printf("Case %d is ", ++t);
        int flag = 0, cnt = 0, root;
        for(i = 1; i <= size; i++) {
            if(indeg[i] > 1) {
                flag = 1;
            }
            if(indeg[i] == 0) {
                cnt++;
                root = i;
            }
        }
        if(cnt != 1 && size)
            flag = 1;
        if(flag == 0 && size) {
            queue<int> Q;
            int in = 0, used[100] = {}, tn;
            Q.push(root);
            used[root] = 1;
            while(!Q.empty()) {
                tn = Q.front();
                Q.pop();
                in++;
                for(vector<Arc>::iterator i = myLink[tn].begin(); i != myLink[tn].end(); i++) {
                    if(!used[i->to]) {
                        used[i->to] = 1;
                        Q.push(i->to);
                    }
                }
            }
            if(in != size)
                flag = 1;
        }
        if(!flag)
            puts("a tree.");
        else
            puts("not a tree.");
    }
    End:
    return 0;
}
