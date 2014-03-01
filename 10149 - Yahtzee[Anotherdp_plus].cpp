#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define STATE 8192 //1<<13
#define DSIZE 13

int DICE[13][5];
int score_cat(int dice[], int cat) {
    int tot = 0, i;
    int D[7];
    switch(cat) {
        case 1:case 2:case 3:case 4:case 5:case 6:
            for(i = 0; i < 5; i++)
                if(dice[i] == cat)
                    tot += cat;
            break;
        case 7: // chance
            for(i = 0; i < 5; i++)
                tot += dice[i];
            break;
        case 8: // three of a kind
            if(dice[0] == dice[2] || dice[1] == dice[3] ||
               dice[2] == dice[4])
            for(i = 0; i < 5; i++)
                tot += dice[i];
            break;
        case 9: // four of a kind
            if(dice[0] == dice[3] || dice[1] == dice[4])
            for(i = 0; i < 5; i++)
                tot += dice[i];
            break;
        case 10: // five of a kind
            if(dice[0] == dice[4])
                tot = 50;
            break;
        case 11: // short straight
            for(i = 0; i <= 6; i++)
                D[i] = 0;
            for(i = 0; i < 5; i++)
                D[dice[i]] = 1;
            for(i = 1; i <= 3; i++) {
                if(D[i] && D[i+1] && D[i+2] && D[i+3])
                    tot = 25;
            }
            break;
        case 12: // long straight
            for(i = 0; i < 4; i++) {
                if(dice[i] != dice[i+1]-1)
                    return 0;
            }
            tot = 35;
            break;
        case 13: //full house
            if(dice[0] == dice[1] && dice[2] == dice[4])
                tot = 40;
            if(dice[0] == dice[2] && dice[3] == dice[4])
                tot = 40;
            break;
    }
    return tot;
}
int count_bit(int n) {
    static int i, j;
    for(i = 0, j = 0; i < 13; i++)
        j += (n>>i)&1;
    return j;
}

int W[10][10], N;
int mx[10], my[10]; // match arr
int lx[10], ly[10]; // label arr
int x[10], y[10]; // used arr
int hungary(int nd) {
    int i;
    x[nd] = 1;
    for(i = 1; i <= N; i++) {
        if(y[i] == 0 && W[nd][i] == lx[nd]+ly[i]) {
            y[i] = 1;
            if(my[i] == 0 || hungary(my[i])) {
                my[i] = nd;
                return 1;
            }
        }
    }
    return 0;
}
int KM() {
    int i, j, k, d;
    memset(mx, 0, sizeof(mx));
    memset(my, 0, sizeof(my));
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    for(i = 1; i <= N; i++)
        for(j = 1; j <= N; j++)
            lx[i] = lx[i] > W[i][j] ? lx[i] : W[i][j];
    for(i = 1; i <= N; i++) {
        while(1) {
            memset(x, 0, sizeof(x));
            memset(y, 0, sizeof(y));
            if(hungary(i))  break;
            d = 0xfffffff;
            for(j = 1; j <= N; j++) {
                if(x[j]) {
                    for(k = 1; k <= N; k++)
                        if(!y[k])
                        d = d < lx[j]+ly[k]-W[j][k] ?
                            d : lx[j]+ly[k]-W[j][k];
                }
            }
            if(d == 0xfffffff)  break;
            for(j = 1; j <= N; j++) {
                if(x[j])    lx[j] -= d;
                if(y[j])    ly[j] += d;
            }
        }
    }
    int res = 0;
    for(i = 1; i <= N; i++) {
        if(my[i])
            res += W[my[i]][i];
    }
    return res < 0 ? 0 : res;
}

int dp[STATE], dp_bonus[STATE]; // = max score
int score[DSIZE][DSIZE]; // score[i][j] = DICE[i] cat j
int arg_dp[STATE]; // choose j
void sol_dp() {
    int i, j, k, p, q;
    for(i = 0; i < 13; i++)
        for(j = 0; j < 13; j++)
            score[i][j] = score_cat(DICE[i], j+1);
    memset(dp, -1, sizeof(dp));
    dp[0] = 0, dp_bonus[0] = 0;
    int bs, s, nstate;
    for(k = 0; k < 6; k++) { // add category
        for(i = 0; i < STATE; i++) {// i = STATE mark
            if(count_bit(i) == k) {
                for(j = 0; j < 13; j++) { // using j dice
                    if(!((i>>j)&1)) {
                        nstate = i|(1<<j);
                        s = dp[i] + score[j][k];
                        bs = 0;
                        if(k == 5 && s >= 63)
                            bs = 35;
                        if(dp[nstate] < s+bs) {
                            dp[nstate] = s+bs;
                            dp_bonus[nstate] = bs;
                            arg_dp[nstate] = j;
                        }
                    }
                }
            }
        }
    }
    int category[13], bonus = 0;
    int mx_score = 0, tmp_score;
    N = 7;
    int tk, kind[13];
    for(i = 0; i < STATE; i++) {
        if(count_bit(i) == 6) {
            for(j = 6; j < 13; j++) { // category
                for(k = 0, tk = 1; k < 13; k++) { // unused dice
                    if(!((i>>k)&1)) {
                        kind[tk] = k;
                        W[tk][j-5] = score[k][j];
                        tk++;
                    }
                }
            }
            tmp_score = dp[i] + KM();
            if(tmp_score > mx_score) {
                mx_score = tmp_score;
                bonus = dp_bonus[i];
                nstate = i;
                for(j = 1; j <= 7; j++)
                    category[j+5] = score[kind[my[j]]][j+5];
            }
        }
    }
    for(i = 5; i >= 0; i--) {
        category[i] = score[arg_dp[nstate]][i];
        nstate ^= 1<<arg_dp[nstate];
    }
    for(i = 0; i < 13; i++)
        printf("%d ", category[i]);
    printf("%d %d\n", bonus, mx_score);
}
int main() {
    int i, j;
    while(1) {
        for(i = 0; i < 13; i++) {
            for(j = 0; j < 5; j++) {
                if(scanf("%d", &DICE[i][j]) != 1)
                    return 0;
            }
            sort(DICE[i], DICE[i]+5);
        }
        sol_dp();
    }
    return 0;
}
