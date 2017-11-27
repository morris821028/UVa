#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <algorithm>
using namespace std;

#define BASE 512
#define MAXX (10000+500+BASE)
int main() {
    int n;
    static int IN[MAXX], OUT[MAXX];
    while (scanf("%d", &n) == 1 && n) {
        memset(IN, 0, sizeof(IN));
        memset(OUT, 0, sizeof(OUT));
        for (int i = 0; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            OUT[x+y+BASE]++;
            IN[x-y+BASE]++;
        }
        
        int ret = 0;
        int sum = 0;
        for (int i = 0; i < MAXX; i++) {
            sum += IN[i];
            ret = max(ret, sum);
            sum -= OUT[i];
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 5
 2  3
 6  6
 9  9
 11  6
 14  4
 0
*/
