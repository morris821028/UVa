#include <stdio.h>
#include <stdlib.h>
int choosePanel[6][6] = {};
int used[6][5] = {};
int cnt[5][6] = {};
void dfs(int idx, int idx2) {
    if(idx2 == 5) {
        dfs(idx+1, 0);
        return ;
    }
    int i, j, k, max = 0xffff;
    if(idx == 6) {
        for(i = 0; i < 6; i++) {
            int m[6] = {}, cnt = 0;
            for(j = 0; j < 5; j++) {
                for(k = 0; k < 6; k++) {
                    if(choosePanel[k][j] == choosePanel[i][j]) {
                        if(!m[k]) {
                            m[k] = 1;
                            cnt++;
                        }
                    }
                }
            }
            if(cnt < max) {
                max = cnt;
            }
            if(max <= 5)
                return;
        }
        max--;
        if(max > 4) {
            for(i = 0; i < 6; i++) {
                printf("%d:", i+1);
                for(j = 0; j < 5; j++)
                    printf(" %d", choosePanel[i][j]);
                            int m[6] = {}, cnt = 0;
                for(j = 0; j < 5; j++) {
                    for(k = 0; k < 6; k++) {
                        if(choosePanel[k][j] == choosePanel[i][j]) {
                            if(!m[k]) {
                                m[k] = 1;
                                cnt++;
                            }
                        }
                    }
                }
                printf(" = %d\n", cnt);
            }
            printf("%d\n", max);
            system("pause");
        }
        return ;
    }
    for(i = 1; i <= 5; i++) {
        if(used[idx][i] == 0) {
            used[idx][i] = 1;
            choosePanel[idx][idx2] = i;
            cnt[idx2][i]++;
            if(cnt[idx2][i] <= 2)
                dfs(idx, idx2+1);
            cnt[idx2][i]--;
            used[idx][i] = 0;
        }
    }
}
int main() {
    dfs(0, 0);
    return 0;
}
