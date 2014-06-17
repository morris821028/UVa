#include <string.h>
#include <stdio.h>

int main() {
    int n, m, cases = 0, i;
    char ign[100], name[100];
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)    break;
        gets(ign);
        while(n--)  gets(ign);
        char ans[100];
        int it = 0;
        double mon, x;
        while(m--) {
            gets(name);
            scanf("%lf %d", &x, &n);
            if(n > it || (n == it && mon > x)) {
                it = n;
                mon = x;
                memcpy(ans, name, sizeof(name));
            }
            gets(ign);
            while(n--)  gets(ign);
        }
        if(cases)   puts("");
        printf("RFP #%d\n%s\n", ++cases, ans);
    }
    return 0;
}
