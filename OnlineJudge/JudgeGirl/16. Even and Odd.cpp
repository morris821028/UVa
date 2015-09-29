#include <stdio.h>

int main() {
        int n, x;
        while (scanf("%d", &n) == 1) {
                int a[1000], b[1000];
                int an = 0, bn = 0;
                for (int i = 0; i < n; i++) {
                        scanf("%d", &x);
                        if (x%2 == 1)
                                a[an++] = x;
                        else
                                b[bn++] = x;
                }
                for (int i = 0; i < an; i++)
                        printf("%d%s", a[i], i == an-1 ? "" : " ");
                puts("");
                for (int i = 0; i < bn; i++)
                        printf("%d%s", b[i], i == bn-1 ? "" : " ");
                puts("");
        }
        return 0;
}

