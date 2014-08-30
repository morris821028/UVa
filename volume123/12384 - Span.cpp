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
using namespace std;

#define maxL (1500000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[131072], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1500000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}

int main() {
    sieve();
    int testcase, n, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        stack< pair<int, int> > stk;
        stk.push(make_pair(131072, -1));
        int ret = 0;
        for (int i = 0; i < n; i++) {
            int x = P[i]%m;
            while (x >= stk.top().first)
                stk.pop();
//            printf("%d\n", i - stk.top().second);
            ret = (ret + i - stk.top().second)%m;
            stk.push(make_pair(x, i));
        }
        printf("%d\n", ret);
    }
    return 0;
}

/*
 3
 
 7 10
 
 10 16
 
 10 7
 */
