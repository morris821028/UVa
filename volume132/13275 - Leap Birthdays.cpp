#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        int dd, mm, yy, Y;
        scanf("%d %d %d %d", &dd, &mm, &yy, &Y);
        printf("Case %d: ", ++cases);
        if (dd != 29 || mm != 2) {
            printf("%d\n", Y-yy);
        } else {
            int c1 = Y/4 - Y/100 + Y/400;
            int c2 = yy/4 - yy/100 + yy/400;
            printf("%d\n", c1-c2);
        }
    }
    return 0;
}
/*
 6
 29 2 1888 1888
 29 2 1888 1910
 29 2 1888 1900
 29 2 1896 1900
 29 2 1888 1901
 29 2 1988 2010
 29 2 1988 2008
 1 1 1988 2010
 31 12 1988 2010
*/
