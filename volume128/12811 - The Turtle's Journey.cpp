#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
#include <map>
using namespace std;

const long long mod = 1000003;
char s[128];
void dfs(long long cmd[]) {
    scanf("%s", s);
    if (s[0] == 'e' || s[0] == ']')    return;
    long long x, ncmd[3] = {};
    scanf("%lld", &x);
    if (s[0] == 'l')
        cmd[0] += x, dfs(ncmd);
    else if (s[0] == 'r' && s[1] == 'i')
        cmd[1] += x, dfs(ncmd);
    else if (s[0] == 'f')
        cmd[2] += x, dfs(ncmd);
    else if (s[0] == 'r' && s[1] == 'e'){
        scanf("%*s");
        dfs(cmd);
        for (int i = 0; i < 3; i++)
            cmd[i] = (cmd[i] * x) %mod;
        dfs(ncmd);
    }
    for (int i = 0; i < 3; i++)
        cmd[i] = (cmd[i] + ncmd[i]) %mod;
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%*s");
        long long cmd[3] = {};
        dfs(cmd);
        printf("%lld %lld %lld\n", cmd[0], cmd[1], cmd[2]);
    }
    return 0;
}
/*
 2
 begin
 forward 10
 left 90
 forward 10
 left 90
 forward 10
 left 90
 forward 10
 left 90
 end
 begin
 forward 10
 left 90
 forward 10
 left 90
 forward 10
 left 90
 forward 10
 left 90
 end */