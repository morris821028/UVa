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

char frame[10][5][5] = {
    {"\\./.",
     ".|..",
     "/o\\."},
    {".o..",
     "/|\\.",
     "/.\\."},
    {"....",
     "....",
     "__\\o"},
    {"....",
     "....",
     "\\_\\o"},
    {"_o_.",
     ".|..",
     "/.\\."},
    {"\\o/.",
     ".|..",
     "/.\\."},
    {"\\o_.",
     "\\|..",
     ".|.."},
    {"\\o/.",
     "\\|/.",
     "...."},
    {"....",
     ".__o",
     "/..|"},
    {".o..",
     "(.).",
     "/.\\."}
};
int main() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; frame[i][j][k]; k++) {
                if (frame[i][j][k] == '.') {
                    frame[i][j][k] = ' ';
                }
            }
        }
    }
    int testcase;
    char s[128];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s", s);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; s[j]; j++) {
                if (j) putchar(' ');
                printf("%s", frame[s[j]-'0'][i]);
            }
            puts("");
        }
        puts("");
    }
    return 0;
}

/*
 2
 171
 151415
 */