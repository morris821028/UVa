#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int main() {
    char s[100];
    while(scanf("%s", s) == 1) {
        int len = strlen(s), i, j;
        sort(s, s+len);
        for(i = 0; i < len; i++) {
            if(s[i] != '0') {
                swap(s[0], s[i]);
                break;
            }
        }
        long long a, b;
        sscanf(s, "%lld", &b);
        sort(s, s+len);
        for(i = 0, j = len-1; i < j; i++, j--)
            swap(s[i], s[j]);
        sscanf(s, "%lld", &a);
        printf("%lld - %lld = %lld = 9 * %d\n", a, b, a-b, (a-b)/9);
    }
    return 0;
}
