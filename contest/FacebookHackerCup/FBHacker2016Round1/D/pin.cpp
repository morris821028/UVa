#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
using namespace std;

const int MAXN = 131072;

int main() {
    srand(time(NULL));
    int testcase;
    int n;
    testcase = 5;
    printf("%d", testcase);
    while (testcase--) {
        n = 16;
        printf("%d\n", n);
        int g[16][16] = {};
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                g[i][j] = rand()%2;
                g[j][i] = 1 - g[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%d ", g[i][j]);
            puts("");
        }
    }
    return 0;
}
