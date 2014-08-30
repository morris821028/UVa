#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

int g[262144], visited[262144];
int main() {
    int testcase, cases = 0;
    int n, x;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &x);
                g[i * n + j] = x;
                visited[i * n + j] = 0;
            }
        }
        
        int ret = 0;
        for (int i = 0; i < n*n; i++) {
            if (visited[i] == 0 && g[i] != i) {
                for (int j = i; !visited[j]; ) {
                    visited[j] = 1;
                    j = g[j];
                    ret++;
                }
                if (i)
                    ret++;
            }
        }
        printf("Case %d: %d\n", ++cases, ret - (g[0] != 0));
    }
    return 0;
}

/*
 2
 3
 7 2 4
 5 0 6
 8 3 1
 2
 3 0
 1 2
 */