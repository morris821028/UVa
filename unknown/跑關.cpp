#include <stdio.h>
#include <stdlib.h>
int map[11][7] = {}, used[11][7];
int time[7][7] = {}, time2[7][7][2];
int map2[11][11] = {}, ans = 0;
int base[11] = {7,7,7,7,7,7,7,7,7,7,7};
void dfs(int idx, int idx2) {
    if(idx == 11) {
        int i, j, tmp = 0xfffff;
        for(i = 0; i < 7; i++)
            for(j = 0; j < 7; j++)
                if(time[i][j] == 1)
                    return;
        for(i = 1; i <= 10; i++) {
            printf("%d :", i);
            for(j = 0; j < 7; j++)
                printf(" %c", map[i][j]+'A'-1);
            puts("");
        }
        system("pause");
        return ;
    }
    int i, j;
    if(idx2 == 7) {
        dfs(idx+1, 0);
        return ;
    }
    for(i = 0; i < 7; i++) {
        if(used[idx][i] == 0) {
            if(time[idx2][i] == 2)
                continue;
            used[idx][i] = 1;
            map[idx][idx2] = i+1;
            time2[idx2][i][time[idx2][i]] = idx;
            time[idx2][i]++;
            int flag = 0;
            if(time[idx2][i] == 2) {
                map2[time2[idx2][i][0]][time2[idx2][i][1]]++;
                map2[time2[idx2][i][1]][time2[idx2][i][0]]++;
                if(map2[time2[idx2][i][0]][time2[idx2][i][1]] >= 2) {
                    flag = 1;
                    base[time2[idx2][i][0]]--, base[time2[idx2][i][1]]--;
                    map2[time2[idx2][i][0]][time2[idx2][i][1]]--;
                    map2[time2[idx2][i][1]][time2[idx2][i][0]]--;
                }
            }
            if(base[idx] >= 4)
                dfs(idx, idx2+1);

            if(time[idx2][i] == 2) {
                map2[time2[idx2][i][0]][time2[idx2][i][1]]--;
                map2[time2[idx2][i][1]][time2[idx2][i][0]]--;
                if(flag == 1) {
                    base[time2[idx2][i][0]]++, base[time2[idx2][i][1]]++;
                    map2[time2[idx2][i][0]][time2[idx2][i][1]]++;
                    map2[time2[idx2][i][1]][time2[idx2][i][0]]++;
                }
            }
            map[idx][idx2] = 0;
            time[idx2][i]--;
            used[idx][i] = 0;
        }
    }
}
int main() {
    dfs(1, 0);
    return 0;
}
/*
1 : A B C D E F G
2 : A B C D F G E
3 : B A D C E F G
4 : B A D C G E F
5 : C D A B F G E
6 : C D A E G B F
7 : D E F G A B C
8 : D F B G C E A
9 : G E F B C D A
10 : G F B E A D C
*/
