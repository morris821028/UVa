#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;
int in[10000], post[10000], n;
int bst[10000][2], pa;
void build(int l, int r, int p, int flag) {
    if(l > r)
        return;
    int i, ppa = pa;
    for(i = l; i <= r; i++) {
        if(in[i] == post[pa]) {
            break;
        }
    }
    if(p != -1)
        bst[p][flag] = pa;
    pa--;
    build(i+1, r, ppa, 1);
    build(l, i-1, ppa, 0);
}
int min_sum, ans;
void dfs(int nd, int sum) {
    if(bst[nd][0] == -1 && bst[nd][1] == -1) {
        if(sum < min_sum)
            min_sum = sum, ans = post[nd];
        if(sum == min_sum && ans > post[nd])
            ans = post[nd];
        return;
    }
    if(bst[nd][0] != -1)
        dfs(bst[nd][0], sum+post[bst[nd][0]]);
    if(bst[nd][1] != -1)
        dfs(bst[nd][1], sum+post[bst[nd][1]]);
}
int main() {
    string line;
    stringstream sin;
    int i;
    while(getline(cin, line)) {
        sin.clear();
        sin << line;
        i = 0;
        while(sin >> in[i])
            i++;
        getline(cin, line);
        sin.clear();
        sin << line;
        i = 0;
        while(sin >> post[i])
            i++;
        n = i, pa = n-1;
        for(i = 0; i < n; i++)
            bst[i][0] = -1, bst[i][1] = -1;
        build(0, n-1, -1, 0);
        min_sum = 0xfffffff;
        dfs(n-1, 0);
        printf("%d\n", ans);
    }
    return 0;
}
