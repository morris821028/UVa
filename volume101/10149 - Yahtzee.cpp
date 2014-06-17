#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define STATE 8192 //1<<13
#define STATE2 64 // bonus use
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
int dp[STATE][STATE2]; // = max score
int score[DSIZE][DSIZE]; // score[i][j] = DICE[i] cat j
int arg_dp[STATE][STATE2][2]; //[0] category, [1] pre(1-6) total score
void sol_dp() {
    int i, j, k, p, q;
    for(i = 0; i < 13; i++)
        for(j = 0; j < 13; j++)
            score[i][j] = score_cat(DICE[i], j+1);
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    int s, nstate, a, b;
    for(k = 0; k < 13; k++) { // add DICE[k]
        for(i = 0; i < STATE; i++) {// i = STATE mark
            if(count_bit(i) == k) {
                for(j = 0; j < 13; j++) {//set category
                    if(!((i>>j)&1)) {
                        s = score[k][j];
                        nstate = i|(1<<j); // new state
                        a = j < 6 ? s : 0;
                        for(p = 0; p < STATE2; p++) {
                            if(dp[i][p] >= 0) {
                                b = (p+a < 63) ? p+a : 63;
                                if(dp[nstate][b] < dp[i][p]+s) {
                                    dp[nstate][b] = dp[i][p]+s;
                                    arg_dp[nstate][b][0] = j;
                                    arg_dp[nstate][b][1] = p;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int mx = 0, bouns = 0;
    for(i = 0; i < 63; i++)
        if(dp[STATE-1][i] > mx) {
            mx = dp[STATE-1][i];
            b = i;
        }
    if(dp[STATE-1][63] >= 0 && dp[STATE-1][63]+35 > mx) {
        mx = dp[STATE-1][63]+35;
        b = 63;
        bouns = 35;
    }
    // backtracking
    int category[13], state = STATE-1;
    int ans[13];
    for(i = 12; i >= 0; i--) {
        category[i] = arg_dp[state][b][0];
        b = arg_dp[state][b][1];
        state ^= 1<<category[i];
        ans[category[i]] = score[i][category[i]];
    }
    for(i = 0; i < 13; i++)
        printf("%d ", ans[i]);
    printf("%d %d\n", bouns, mx);
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
        //puts("==== START");
        sol_dp();
    }
    return 0;
}
