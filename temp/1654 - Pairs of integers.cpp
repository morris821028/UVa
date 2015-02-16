#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
int getLength(int x) {
    static char buf[16];
    sprintf(buf, "%d", x);
    return (int) strlen(buf);
}
int main() {
    int testcase, n, t10[10] = {1};
    for (int i = 1; i < 10; i++)
        t10[i] = t10[i-1] * 10;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        
        vector< pair<int, int> > ret;
        for (int i = 0; i < 10 && t10[i] <= n; i++) {
            int front = n / t10[i], back = n % t10[i];
            int u = front / 11;
            int p = front - u * 11;
            if (p < 10) {
                int x = u * 10 * t10[i] + p * t10[i] + back / 2;
                int y = u * t10[i] + back / 2;
                if (x + y == n && getLength(x) > getLength(y))
                    ret.push_back(make_pair(x, y));
            }
            if (p > 0) {
                int x = u * 10 * t10[i] + (p - 1) * t10[i] + (back + t10[i])/2;
                int y = u * t10[i] + (back + t10[i])/2;
                if (x + y == n && getLength(x) > getLength(y))
                    ret.push_back(make_pair(x, y));
            }
        }
        
        sort(ret.begin(), ret.end());
        ret.resize(unique(ret.begin(), ret.end()) - ret.begin());
        printf("%d\n", (int) ret.size());
        for (int i = 0; i < ret.size(); i++) {
            int lx = getLength(ret[i].first);
            char format[] = "%d + %0?d = %d\n";
            format[7] = lx - 1 + '0';
            printf(format, ret[i].first, ret[i].second, n);
        }
        if (testcase)
            puts("");
    }
    return 0;
}
/*

*/