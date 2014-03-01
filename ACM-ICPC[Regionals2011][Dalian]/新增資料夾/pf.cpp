#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<map>
#define mem(x) memset(x,0,sizeof(x))
using namespace std;

typedef long long ll;
char g[200][50000];
int main(){
    long long n, m, q, i, j, k;
    while(scanf("%lld %lld %lld", &n, &m, &q) == 3) {
        for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
                g[i][j] = 0;
        char cmd[100];
        long long x, y, r, c, l, w, W;
        while(q--) {
            scanf("%s", cmd);
            if(!strcmp(cmd, "Circle")) {
                scanf("%lld %lld %lld %lld", &x, &y, &r, &c);
                for(i = x-r; i <= x+r; i++) {
                    for(j = y-r; j <= y+r; j++) {
                        if(i < 0 || j < 0 || i >= n || j >= m)
                            continue;
                        if((i-x)*(i-x)+(j-y)*(j-y) > r*r)
                            continue;
                        g[i][j] = c;
                    }
                }
            } else if(!strcmp(cmd, "Diamond")) {
                scanf("%lld %lld %lld %lld", &x, &y, &r, &c);
                for(i = x-r; i <= x+r; i++) {
                    for(j = y-r; j <= y+r; j++) {
                        if(i < 0 || j < 0 || i >= n || j >= m)
                            continue;
                        if(abs(i-x)+abs(j-y) > r)
                            continue;
                        g[i][j] = c;
                    }
                }
            } else if(!strcmp(cmd, "Rectangle")) {
                scanf("%lld %lld %lld %lld %lld", &x, &y, &l, &w, &c);
                for(i = x; i < x+l; i++) {
                    for(j = y; j < y+w; j++) {
                        if(i < 0 || j < 0 || i >= n || j >= m)
                            continue;
                        g[i][j] = c;
                    }
                }
            } else if(!strcmp(cmd, "Triangle")) {
                scanf("%lld %lld %lld %lld", &x, &y, &w, &c);
                int tw = w;
                for(i = x; i <= x+(tw+1)/2+52; i++, w-=2) {
                    for(j = y-(w+1)/2+1; j <= y+(w+1)/2-1; j++) {
                        if(i < 0 || j < 0 || i >= n || j >= m)
                            continue;
                        g[i][j] = c;
                    }
                }
            }
        }
        int cnt[10] = {};
        for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
                cnt[g[i][j]]++;
        for(i = 1; i < 10; i++) {
            if(i != 1)
                printf(" ");
            printf("%d", cnt[i]);
        }
        puts("");
    }
    return 0;
}
/*
8 8 1
Triangle 4 4 3 2
20 20 1
Triangle 10 10 1 2
20 20 1
Triangle 10 10 5 2
*/
