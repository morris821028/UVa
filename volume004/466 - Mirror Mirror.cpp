#include <stdio.h>
#include <string.h>
void rotate(char a[][20], char buf[][20], int n) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            buf[j][n-1-i] = a[i][j];
}
void reflect(char a[][20], char buf[][20], int n) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            buf[n-1-i][j] = a[i][j];
}
int main() {
    int n, cases = 0;
    char a[20][20], b[20][20], c[20][20], d[20][20];
    int i, j, k;
    while(scanf("%d", &n) == 1) {
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(c, 0, sizeof(c));
        memset(d, 0, sizeof(d));
        for(i = 0; i < n; i++)
            scanf("%s %s", a[i], b[i]);
        printf("Pattern %d was ", ++cases);
        if(memcmp(a, b, sizeof(a)) == 0) {
            puts("preserved.");
            continue;
        }
        memcpy(c, a, sizeof(c));
        for(i = 0; i < 3; i++) {
            rotate(c, d, n);
            if(memcmp(d, b, sizeof(c)) == 0) {
                printf("rotated %d degrees.\n", i*90+90);
                break;
            }
            memcpy(c, d, sizeof(c));
        }
        if(i != 3)
            continue;
        reflect(a, c, n);
        if(memcmp(c, b, sizeof(c)) == 0) {
            puts("reflected vertically.");
            continue;
        }
        for(i = 0; i < 3; i++) {
            rotate(c, d, n);
            if(memcmp(d, b, sizeof(c)) == 0) {
                printf("reflected vertically and rotated %d degrees.\n", i*90+90);
                break;
            }
            memcpy(c, d, sizeof(c));
        }
        if(i != 3)
            continue;
        puts("improperly transformed.");
    }
    return 0;
}
