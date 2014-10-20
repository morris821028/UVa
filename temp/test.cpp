#include <cstdio>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <cctype>
#include <ctime>
#include <set>
#include <climits>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cmath>
#include <string>
#include <list>

#define INPUT_FILE "in.txt"
#define OUTPUT_FILE "out.txt"

using namespace std;

typedef long long LL;
const int INF = INT_MAX / 2;

void setfile() {
    freopen(INPUT_FILE,"r",stdin);
    freopen(OUTPUT_FILE,"w",stdout);
}

const int maxn = 105;

struct Node {
    int cnt,e[maxn],col;
};

Node node[maxn];
bool know[maxn],conflict,team1[maxn],vis[maxn];
bool g[maxn][maxn],dp[maxn * 2][maxn * 2];
int n,sz[maxn],sz_zero[maxn],sz_one[maxn],rcnt;
int pid[maxn][maxn];

//染色
void dfs(int now,int id) {
    if(node[now].col == 0) sz_zero[id]++;
    else sz_one[id]++;
    pid[id][sz[id]++] = now;
    for(int i = 0;i < node[now].cnt;i++) {
        int nowid = node[now].e[i];
        if(node[nowid].col == -1) {
            node[nowid].col = node[now].col ^ 1;
            dfs(nowid,id);
        } else {
            if(node[nowid].col == node[now].col) {
                conflict = true;
            }
        }
    }
}

//???通?并且?行染色
void judge() {
    rcnt = 0;
    for(int i = 1;i <= n;i++) {
        if(node[i].col == -1) {
            node[i].col = 0;
            rcnt++;
            dfs(i,rcnt);
        }
    }
}

//?第i??通?中?色?col的?加入?中
void addteam(int i,int col) {
    vis[i] = true;
    if(node[i].col == col) {
        team1[i] = true;
    }
    for(int j = 0;j < node[i].cnt;j++) {
        int chid = node[i].e[j];
        if(vis[chid] == false) {
            addteam(chid,col);
        }
    }
}

//?出答案
void print_path(int i,int now) {
    if(i == 0) return;
    if(dp[i - 1][now - sz_zero[i]]) {
        memset(vis,0,sizeof(vis));
        addteam(pid[i][0],0);
        print_path(i - 1,now - sz_zero[i]);
    } else {
        memset(vis,0,sizeof(vis));
        addteam(pid[i][0],1);
        print_path(i - 1,now - sz_one[i]);
    }
}


void work() {
    dp[0][0] = true;
    //背包
    for(int i = 1;i <= rcnt;i++) {
        for(int j = 0;j <= n;j++) {
            if(dp[i - 1][j] == true) {
                dp[i][j + sz_zero[i]] = true;
                dp[i][j + sz_one[i]] = true;
            }
        }
    }
    int val = -1;
    for(int j = n / 2;j >= 1;j--) {
        if(dp[rcnt][j] == true) {
            val = j; break;
        }
    }
    if(val == -1) {
        puts("No solution");
    } else {
        print_path(rcnt,val);
        printf("%d",val);
        for(int i = 1;i <= n;i++) if(team1[i]) printf(" %d",i);
        printf("\n%d",n - val);
        for(int i = 1;i <= n;i++) if(!team1[i]) printf(" %d",i);
        putchar('\n');
    }
}

int main() {
    int tmp;
    while(scanf("%d",&n) != EOF) {
        memset(node,0,sizeof(node));
        memset(sz,0,sizeof(sz));
        memset(sz_zero,0,sizeof(sz_zero));
        memset(sz_one,0,sizeof(sz_one));
        memset(dp,0,sizeof(dp));
        memset(team1,0,sizeof(team1));
        memset(g,0,sizeof(g));
        //?入并且建立??
        for(int i = 1;i <= n;i++) {
            while(scanf("%d",&tmp),tmp) {
                g[i][tmp] = true;
            }
            node[i].col = -1;
        }

        for(int i = 1;i <= n;i++) {
            for(int j = 1;j <= n;j++) {
                if(!(g[i][j] && g[j][i]) && i != j) {
                    node[i].e[node[i].cnt++] = j;
                    printf("%d -> %d\n", i, j);
                }
            }
        }

        //染色并且???通?
        conflict = false;
        judge();
        if(conflict) {
            puts("No solution");
        } else {
            work();
        }
    }
    return 0;
}
