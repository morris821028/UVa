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

int main() {
    int testcase, cases = 0;
    char s[1024], type1[1024], type2[1024];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s", s);
        int row, col, D = col - 2;
        int ok = 1;
        col = (int)strlen(s);
        D = col - 2;
        row = D * 2 + 3;
        for (int i = 0; i < col; i++)
            type1[i] = '-', type2[i] = '.';
        type1[0] = type1[col-1] = '.';
        type2[0] = type2[col-1] = '|';
        type1[col] = type2[col] = '\0';
        for (int i = 0; i <= row; i++) {
            if (i)  scanf("%s", s);
            if (!strcmp(s, "*")) {
                if (i == row)
                    break;
                ok = 0;
                break;
            }
            if (i == 0 || i == row - 1 || i == D + 1) {
                ok &= !strcmp(s, type1);
//                printf("%s === %s\n", type1, s);
            } else {
                ok &= !strcmp(s, type2);
//                printf("%s === %s\n", type2, s);
            }
        }
        while (strcmp(s, "*")) {
            ok = 0;
            scanf("%s", s);
        }
        printf("Case %d: ", ++cases);
        if (ok && D >= 0)
            printf("%d\n", D);
        else
            puts("Bad");
    }
    return 0;
}

/*
 2
 .---.
 |...|
 |...|
 |...|
 .---.
 |...|
 |...|
 |...|
 .---.
 *
 .---.
 |...|
 |...|
 |...|
 .---.
 |...|
 |...|
 .---.
 * 
 */