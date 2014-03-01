#include <stdio.h>
inline bool test(char a, char b) {
    return a == 'r' && b == 's' ||
        a == 's' && b == 'p' ||
        a == 'p' && b == 'r';
}
inline int ReadInt(int *x) {
    static char c;
    while((c = getchar()))    {
        if(c >= '0' && c <= '9')
            break;
    }
    *x = c-'0';
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    return 1;
}
int main() {
    int n, k, m, i, first = 0;
    int p[105][2], x, y;
    char a[20], b[20];
    while(scanf("%d %d", &n, &k) == 2) {
        m = k*n*(n-1)/2;
        if(first)   puts("");
        first = 1;
        for(i = 1; i <= n; i++)
            p[i][0] = p[i][1] = 0;
        while(m--) {
            ReadInt(&x);
            a[0] = getchar();
            ReadInt(&y);
            b[0] = getchar();
            while(getchar() != '\n');
            if(test(a[0], b[0]))
                p[x][0]++, p[y][1]++;
            else if(test(b[0], a[0]))
                p[y][0]++, p[x][1]++;
        }
        for(i = 1; i <= n; i++)
            if(p[i][0]+p[i][1])
                printf("%.3f\n", (float)p[i][0]/(p[i][0]+p[i][1]));
            else
                puts("-");
    }
    return 0;
}
