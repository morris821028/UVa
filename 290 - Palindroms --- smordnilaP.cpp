#include <stdio.h>
#include <string.h>

void solve(int o[], int base) {
    int a[500] = {};
    int i, j, k, len;
    int cnt = 0;
    len = 299;
    while(o[len] == 0)  len--;
    do {
        for(i = 0, j = len; i < j; i++, j--)
            if(o[i] != o[j])
                break;
        if(i >= j)
            break;
        cnt++;
        for(i = 0; i <= len; i++)
            a[i] = o[i]+o[len-i];
        for(i = 0; i <= len+10; i++) {
            if(a[i] >= base) {
                a[i+1] += a[i]/base;
                a[i] %= base;
            }
            o[i] = a[i];
        }
        len += 10;
        while(o[len] == 0)  len--;
    } while(1);
    printf("%d", cnt);
}
int main() {
    char s[105];
    while(scanf("%s", &s) == 1) {
        int i, j, k, len = strlen(s), base = 0;
        for(i = 0; i < len; i++) {
            if(s[i] <= '9')
                s[i] -= '0';
            else
                s[i] -= 'A'-10;
            if(s[i] > base)
                base = s[i];
        }
        if(base == 0)   base = 1;
        for(i = 15; i > base; i--) {
            if(i != 15) printf(" ");
            int o[500] = {};
            for(j = len-1, k = 0; j >= 0; j--, k++)
                o[k] = s[j];
            solve(o, i);
        }
        for(i = base; i >= 2; i--) {
            if(i != 15) printf(" ");
            printf("?");
        }
        puts("");
    }
    return 0;
}
