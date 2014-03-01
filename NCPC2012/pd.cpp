#include <stdio.h>
#include <iostream>
using namespace std;
int inv(int x, int y, int mod) {
    if(y == 0)    return 1;
    if(y&1) return x*inv(x*x%mod, y/2, mod)%mod;
    return inv(x*x%mod, y/2, mod);
}
int main() {
    freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);
    int t;
    char s[50];
    scanf("%d", &t);
    printf("%4d\n", t);
    while(t--) {
        int n, m, i, j, k;
        scanf("%d", &n);
        printf("%4d\n", n);
        int M[3][6] = {}, tmp;
        m = 2*n;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%d", &M[i][j]);
                M[i][j] = (M[i][j]%11+11)%11;
            }
            M[i][i+n] = 1;
        }
        scanf("%s", s);
        for(i = 0; i < n; i++) {
            int ch = -1;
            for(j = i; j < n; j++)
                if(M[j][i]) {
                    ch = j;break;
                }
            if(ch == -1)    puts("ERROR");
            for(j = 0; j < m; j++)
                swap(M[ch][j], M[i][j]);
            tmp = inv(M[i][i],9,11);
            for(j = 0; j < m; j++) {
                M[i][j] = M[i][j]*tmp;
                M[i][j] = (M[i][j]%11+11)%11;
            }
            for(j = 0; j < n; j++) {
                if(i == j)  continue;
                tmp = M[j][i]*inv(M[i][i],9,11);
                for(k = 0; k < m; k++) {
                    M[j][k] = M[j][k] - M[i][k]*tmp;
                    M[j][k] = (M[j][k]%11+11)%11;
                }
            }

        }
        for(i = 0; i < n;i++) {
            for(j = n; j < m; j++)
                printf("%4d", M[i][j]);
            puts("");
        }
        int x1, x2, x3;
        for(i = 0; i < 12; i += n) {
            if(n == 2) {
                s[i] -= '0';
                s[i+1] -= '0';
                x1 = M[0][2]*s[i] + M[0][3]*s[i+1];
                x2 = M[1][2]*s[i] + M[1][3]*s[i+1];
                x1 %= 11, x2 %= 11;
                if(x1 != 10)    x1 += '0';
                else x1 = ':';
                if(x2 != 10)    x2 += '0';
                else x2 = ':';
                printf("%c%c", x1, x2);
            } else {
                s[i] -= '0';
                s[i+1] -= '0';
                s[i+2] -= '0';
                x1 = M[0][3]*s[i] + M[0][4]*s[i+1] + M[0][5]*s[i+2];
                x2 = M[1][3]*s[i] + M[1][4]*s[i+1] + M[1][5]*s[i+2];
                x3 = M[2][3]*s[i] + M[2][4]*s[i+1] + M[2][5]*s[i+2];
                x1 %= 11, x2 %= 11, x3 %= 11;
                if(x1 != 10)    x1 += '0';
                else x1 = ':';
                if(x2 != 10)    x2 += '0';
                else x2 = ':';
                if(x3 != 10)    x3 += '0';
                else x3 = ':';
                printf("%c%c%c", x1, x2, x3);
            }
        }
        puts("");
    }
    return 0;
}
/*
   2
   2
   2   1
   3   2
6:19278694:2
   3
   1   1   1
   1   2   2
   1   2   3
26242669:976
*/
