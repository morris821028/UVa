#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
    int n, i, a[10];
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            a[i] = n-i;
        do {
            for(i = 0; i < n; i++)
                putchar(a[i]+'0');
            puts("");
        } while(prev_permutation(a, a+n));
    }
    return 0;
}
