#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <assert.h>
using namespace std;

const int PINS = 10;
const int FRAMES = 10;
int64_t dp[11][305][4] = {};
// [frame][score][00/01/10/11]
// 00, none
// 01, spare
// 10, strike
// 11, strike -> strike
void init() {
    dp[0][0][0] = 1;
    for (int i = 0; i < FRAMES; i++) {
        for (int j = 0; j <= 300; j++) {
            for (int k = 0; k < 4; k++) {
                if (dp[i][j][k] == 0)
                    continue;
                for (int r1 = 0; r1 <= PINS; r1++) {
                    for (int r2 = 0; r2 <= PINS-r1; r2++) {
                        if (k == 0) {
                            int kk = 0, ss = j+r1+r2;
                            if (i+1 == FRAMES) {    // last frame
                                if (r1 == PINS) {
                                    kk = 2;
                                    for (int r1 = 0; r1 <= PINS; r1++) {
                                        if (r1 == PINS) {
                                            for (int r2 = 0; r2 <= PINS; r2++)
                                                dp[i+1][ss+r1+r2][kk] += dp[i][j][k];
                                        } else {
                                            for (int r2 = 0; r2 <= PINS-r1; r2++)
                                                dp[i+1][ss+r1+r2][kk] += dp[i][j][k];
                                        }
                                    }
                                } else if (r1+r2 == PINS) {
                                    kk = 1;
                                    for (int r1 = 0; r1 <= PINS; r1++)
                                        dp[i+1][ss+r1][kk] += dp[i][j][k];
                                } else {
                                    kk = 0;
                                    dp[i+1][ss][kk] += dp[i][j][k];
                                }
                            } else {
                                if (r1 == PINS)
                                    kk = 2;
                                else if (r1+r2 == PINS)
                                    kk = 1;
                                dp[i+1][ss][kk] += dp[i][j][k];
                            }
                        } else if (k == 1) {
                            int kk = 0, ss = j+r1*2+r2;
                            if (i+1 == FRAMES) {
                                if (r1 == PINS) {
                                    kk = 2;
                                    for (int r1 = 0; r1 <= PINS; r1++) {
                                        if (r1 == PINS) {
                                            for (int  r2 = 0; r2 <= PINS; r2++)
                                                dp[i+1][ss+r1+r2][kk] += dp[i][j][k];
                                        } else {
                                            for (int  r2 = 0; r2 <= PINS-r1; r2++)
                                                dp[i+1][ss+r1+r2][kk] += dp[i][j][k];
                                        }
                                    }
                                } else if (r1+r2 == PINS) {
                                    kk = 1;
                                    for (int r1 = 0; r1 <= PINS; r1++)
                                        dp[i+1][ss+r1][kk] += dp[i][j][k];
                                } else {
                                    kk = 0;
                                    dp[i+1][ss][kk] += dp[i][j][k];
                                }
                            } else {
                                if (r1 == PINS)
                                    kk = 2;
                                else if (r1+r2 == PINS)
                                    kk = 1;
                                dp[i+1][ss][kk] += dp[i][j][k];
                            }
                        } else if (k == 2) {
                            int kk = 0, ss = j;
                            if (i+1 == FRAMES) {
                                if (r1 == PINS) {
                                    kk = 3, ss += r1*2;
                                    for (int r1 = 0; r1 <= PINS; r1++) {
                                        if (r1 == PINS) {
                                            for (int  r2 = 0; r2 <= PINS; r2++)
                                                dp[i+1][ss+r1*2+r2][kk] += dp[i][j][k];
                                        } else {
                                            for (int  r2 = 0; r2 <= PINS-r1; r2++)
                                                dp[i+1][ss+r1*2+r2][kk] += dp[i][j][k];
                                        }
                                    }
                                } else if (r1+r2 == PINS) {
                                    kk = 1, ss += r1*2+r2*2;
                                    for (int r1 = 0; r1 <= PINS; r1++)
                                        dp[i+1][ss+r1][kk] += dp[i][j][k];
                                } else {
                                    kk = 0, ss += r1*2+r2*2;
                                    dp[i+1][ss][kk] += dp[i][j][k];
                                }
                            } else {
                                if (r1 == PINS)
                                    kk = 3, ss += r1*2;
                                else if (r1+r2 == PINS)
                                    kk = 1, ss += r1*2+r2*2;
                                else
                                    kk = 0, ss += r1*2+r2*2;
                                dp[i+1][ss][kk] += dp[i][j][k];
                            }
                        } else if (k == 3) {
                            int kk = 0, ss = j;
                            if (i+1 == FRAMES) {
                                if (r1 == PINS) {
                                    kk = 3, ss += r1*3;
                                    for (int r1 = 0; r1 <= PINS; r1++) {
                                        if (r1 == PINS) {
                                            for (int  r2 = 0; r2 <= PINS; r2++)
                                                dp[i+1][ss+r1*2+r2][kk] += dp[i][j][k];
                                        } else {
                                            for (int  r2 = 0; r2 <= PINS-r1; r2++)
                                                dp[i+1][ss+r1*2+r2][kk] += dp[i][j][k];
                                        }
                                    }
                                } else if (r1+r2 == PINS) {
                                    kk = 1, ss += r1*3+r2*2;
                                    for (int r1 = 0; r1 <= PINS; r1++)
                                        dp[i+1][ss+r1][kk] += dp[i][j][k];
                                } else {
                                    kk = 0, ss += r1*3+r2*2;
                                    dp[i+1][ss][kk] += dp[i][j][k];
                                }
                            } else {
                                if (r1 == PINS)
                                    kk = 3, ss += r1*3;
                                else if (r1+r2 == PINS)
                                    kk = 1, ss += r1*3+r2*2;
                                else
                                    kk = 0, ss += r1*3+r2*2;
                                dp[i+1][ss][kk] += dp[i][j][k];
                            }
                        }
                    }
                }
            }
        }
    }
}
int main() {
    init();
    int s;
    while (scanf("%d", &s) == 1 && s >= 0) {
        int64_t ret = 0;
        for (int i = 0; i < 4; i++)
            ret += dp[FRAMES][s][i];
        printf("%lld\n", ret);
    }
    return 0;
}

