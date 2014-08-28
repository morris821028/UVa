#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <functional>
using namespace std;
#define MAXN 131072
char s[MAXN];
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s", s);
        int ret = 0, O = 0;
        for (int i = 0; s[i]; i++) {
            O = s[i] == 'O' ? O + 1 : 0;
            ret += O;
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*

 */