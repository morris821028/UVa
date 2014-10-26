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

int main() {
    int testcase;
    int H, W, N, x, y;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d %d", &H, &W, &N);
        vector< pair<int, int> > D;
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &x, &y);
            D.push_back(make_pair(x, y));
        }
        sort(D.begin(), D.end());
        int A[26];
        for (int i = 1; i <= H; i++)
            A[i] = i - 1;
        for (int i = 0; i < N; i++)
            swap(A[D[i].second], A[D[i].second + 1]);
        for (int i = 1; i <= H; i++) {
            if (i != 1) putchar(' ');
            printf("%c", A[i] + 'A');
        }
        puts("");
    }
    return 0;
}
/*
 3
 5 30 2
 10 3
 20 1
 5 30 7
 4 4
 8 3
 12 2
 16 1
 20 2
 24 3
 28 4
 5 30 2
 10 2
 20 1
 */