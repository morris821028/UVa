#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int n, m;
    int i, j, k, p, q;
    while(scanf("%d %d", &n, &m) == 2) {
        int x, t;
        int g[101][21], gt[101];
        int ch[101][21][101][2], cht[101][21];
        int used[101] = {};
        for(i = 0; i < n; i++) {
            scanf("%d %d", &x, &t);
            gt[x] = t, used[x] = 1;
            for(j = 1; j <= t; j++)
                scanf("%d", &g[x][j]), cht[x][j] = 0;
        }
        while(m--) {
            scanf("%d %d %d %d", &i, &p, &j, &q);
            ch[i][p][cht[i][p]][0] = j;
            ch[i][p][cht[i][p]++][1] = q;
            ch[j][q][cht[j][q]][0] = i;
            ch[j][q][cht[j][q]++][1] = p;
        }
        int hh, mm, hi, hj;
        for(hi = 0; hi < 5; hi++) {
            scanf("%d %d %d %d %d %d", &hh, &mm, &i, &p, &j, &q);
            int sche[101][21][2];
            for(hj = 1; hj <= 100; hj++) {
                if(used[hj]) {
                    sche[hj][1][0] = 360;
                    for(k = 2; k <= gt[hj]; k++)
                        sche[hj][k][0] = sche[hj][k-1][0]+g[hj][k]+1;
                    sche[hj][gt[hj]][1] = 360;
                    for(k = gt[hj]-1; k >= 1; k--)
                        sche[hj][k][1] = sche[hj][k+1][1]+g[hj][k+1]+1;
                }
            }
            int Q[1000][2], Qt = 0;
            int ar[101][21] = {}, ud[101][21] = {};
            int as[101][21] = {};
            memset(ar, 127, sizeof(ar));
            Q[0][0] = i, Q[0][1] = p;

            ar[i][p] = hh*60 + mm;
            for(hj = 0; hj <= Qt; hj++) {
                i = Q[hj][0], p = Q[hj][1];
                ud[i][p] = 0;
                if(p != gt[i]) {
                    if(sche[i][p][0] > ar[i][p+1]) {
                        if(ar[i][p+1] > sche[i][p][0]+g[i][p+1]+1) {
                            ar[i][p+1] = sche[i][p][0]+g[i][p+1]+1;
                            if(!ud[i][p+1]) {
                                ud[i][p+1] = 1;
                                Q[++Qt][0] = i, Q[Qt][1] = p+1;
                            }
                        }
                    } else {
                        int tmp = ar[i][p];
                        if((tmp-1-sche[i][p][0])%5 == 0)    tmp--;
                        while((tmp-sche[i][p][0])%5 != 0)   tmp++;
                        if(ar[i][p+1] > tmp+g[i][p+1]+1) {
                            ar[i][p+1] = tmp+g[i][p+1]+1;
                            if(!ud[i][p+1]) {
                                ud[i][p+1] = 1;
                                Q[++Qt][0] = i, Q[Qt][1] = p+1;
                            }
                        }
                    }
                }
                if(p != 1) {
                    if(sche[i][p][1] > ar[i][p]) {
                        if(ar[i][p-1] > sche[i][p][1]+g[i][p]+1) {
                            ar[i][p-1] = sche[i][p][1]+g[i][p]+1;
                            if(!ud[i][p-1]) {
                                ud[i][p-1] = 1;
                                Q[++Qt][0] = i, Q[Qt][1] = p-1;
                            }
                        }
                    } else {
                        int tmp = ar[i][p];
                        if((tmp-1-sche[i][p][1])%5 == 0)    tmp--;
                        while((tmp-sche[i][p][1])%5 != 0)   tmp++;
                        if(ar[i][p-1] > tmp+g[i][p]+1) {
                            ar[i][p-1] = tmp+g[i][p]+1;
                            if(!ud[i][p-1]) {
                                ud[i][p-1] = 1;
                                Q[++Qt][0] = i, Q[Qt][1] = p-1;
                            }
                        }
                    }
                }
                for(k = 0; k < cht[i][p]; k++) {
                    if(ar[ch[i][p][k][0]][ch[i][p][k][1]] > ar[i][p]) {
                        ar[ch[i][p][k][0]][ch[i][p][k][1]] = ar[i][p];
                        if(!ud[ch[i][p][k][0]][ch[i][p][k][1]]) {
                            ud[ch[i][p][k][0]][ch[i][p][k][1]] = 1;
                            Q[++Qt][0] = ch[i][p][k][0], Q[Qt][1] = ch[i][p][k][1];
                        }
                    }
                }
            }
            printf("%d\n", ar[j][q]-hh*60-mm);
        }
    }
    return 0;
}
