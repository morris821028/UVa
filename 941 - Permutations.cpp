#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    int t, i, j, k;
    long long f[21] = {1, 1}, p;
    char str[30];
    for(i = 2; i <= 20; i++)
        f[i] = f[i-1]*i;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", str);
        int n = strlen(str);
        sort(str, str+n);
        scanf("%lld", &p);
        p++;
        int used[21] = {};
        for(i = 0; i < n; i++) {
            for(j = 0; j <= n; j++) {
                if(f[n-i-1]*j >= p)
                    break;
            }
            j--;
            p -= f[n-i-1]*j;
            for(k = 0; k < n; k++) {
                if(used[k] == 0) {
                    if(j == 0) {
                        printf("%c", str[k]);
                        used[k] = 1;
                        break;
                    }
                    j--;
                }
            }
        }
        puts("");
    }
    return 0;
}
