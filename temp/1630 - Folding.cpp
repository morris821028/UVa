#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
using namespace std;
#define MAXN 105
#define INF 0x3f3f3f3f
string dp[MAXN][MAXN];
char s[MAXN];
int N;
string num2str(int x) {
    string s;
    stringstream sin(s);
    sin << x;
    return sin.str();
}
string fold(int l, int r, int c, int &f) {
    int n = r-l+1;
    if (n%c) {
        f = 0;
        return "";
    }
    int ok = 1;
    for (int i = l; i <= r; i += c) {
        for (int j = 0; j < c; j++) {
            ok &= s[i+j] == s[l+j];
        }
        if (!ok) {
            f = 0;
            return "";
        }
    }
    f = 1;
    string ret = num2str(n/c) + "(" + dp[l][l+c-1] + ")";
    return ret;
}
int main() {
    while (scanf("%s", s) == 1) {
        N = (int) strlen(s);
        for (int i = 0; i < N; i++) {
            for (int j = 0; i + j < N; j++) {
                int l = j, r = j+i;
                if (l == r) {
                    dp[l][r] = string(1, s[j]);
                } else {
                    int mn = r-l+1;
                    dp[l][r] = string(s+l).substr(0, mn);
                    for (int k = l; k < r; k++) {
                        if (mn > dp[l][k].size() + dp[k+1][r].size()) {
                            mn = (int) (dp[l][k].size() + dp[k+1][r].size());
                            dp[l][r] = dp[l][k] + dp[k+1][r];
                        }
                    }
                    for (int k = l; k < r; k++) {
                        int f = 0;
                        string t = fold(l, r, k-l+1, f);
                        if (f) {
                            if (mn > t.length()) {
                                mn = (int) t.length();
                                dp[l][r] = t;
                            }
                        }
                    }
                }
            }
        }
        printf("%s\n", dp[0][N-1].c_str());
    }
    return 0;
}
/*
*/