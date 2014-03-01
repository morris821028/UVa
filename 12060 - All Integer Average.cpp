#include <stdio.h>
#include <string.h>
int gcd(int x, int y) {
    int t;
    while(x%y)
        t = x, x = y, y = t%y;
    return y;
}
int getNumLen(int n) {
    char m[15];
    sprintf(m, "%d", n);
    return strlen(m);
}
int main() {
    int n;
    int cases = 0;
    while(scanf("%d", &n), n) {
        int i, x, y, sum = 0;
        for(i = 0; i < n; i++)
            scanf("%d", &x), sum += x;
        int flag = 1;
        if(sum < 0) flag = -1, sum *= -1;
        x = sum%n, y = n, sum /= n;
        int g = gcd(x, y);
        x /= g, y /= g;
        printf("Case %d:\n", ++cases);
        if(sum >= 1) {
            if(y == 1) {
                if(flag < 0)    printf("- ");
                printf("%d\n", sum);
            } else {
                int w = 0;
                if(flag < 0)    w += 2;
                w += getNumLen(sum)+getNumLen(y);
                for(i = w-getNumLen(x); i > 0; i--)  putchar(' ');
                printf("%d\n", x);
                if(flag < 0)    printf("- ");
                printf("%d", sum);
                for(i = getNumLen(y); i > 0; i--)   putchar('-');
                puts("");
                for(i = w-getNumLen(y); i > 0; i--) putchar(' ');
                printf("%d\n", y);
            }
        } else {
            if(y == 1) {
                if(flag < 0)
                    printf("- ");
                printf("%d\n", sum);
            } else {
                int w = 0;
                if(flag < 0)    w += 2;
                w += getNumLen(y);
                for(i = w-getNumLen(x); i > 0; i--)  putchar(' ');
                printf("%d\n", x);
                if(flag < 0)    printf("- ");
                for(i = getNumLen(y); i > 0; i--)   putchar('-');
                puts("");
                for(i = w-getNumLen(y); i > 0; i--) putchar(' ');
                printf("%d\n", y);
            }
        }

    }
    return 0;
}
