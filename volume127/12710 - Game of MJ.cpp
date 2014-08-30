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

int main() {
    int testcase, n, L, B, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        long long m0, m1, m2;
        m0 = m1 = m2 = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &L, &B);
            L--;
            if (B%3 == 2) { // 2, 1, 2, 1 ...
                m1 += (L/2) * (B - 1);
                m2 += ((L+1)/2) * (B - 1);
            } else if (B%3 == 1) { // 1, 1, 1, 1 ...
                m1 += L * (B - 1);
            } else {
                m0 += L * (B - 1);
            }
        }
        printf("Case %d: ", ++cases);
        if (m0 + m1 + m2 == 0) {
            puts("Draw");
        } else if (m1+ m2 == 0) {
            puts("J");
        } else {
            if (m0%2 == 0) {
                if (m1 == 0 || m2 == 0) {
                    if (m1 <= 2 && m2 <= 2)
                        puts("Draw");
                    else
                        puts("J");
                } else {
                    puts("M");
                }
            } else {
                if (m1 == m2) {
                    puts("J");
                } else if (abs(m1 - m2) >= 3) {
                    puts("M");
                } else {
                    puts("Draw");
                }
            }
        }
    }
    return 0;
}

/*
 3
 1
 5 2
 2
 3 2
 2 6
 1
 2 2
 */