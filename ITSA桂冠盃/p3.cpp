#include <stdio.h>
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
char D[200000][10];
int A[10], B[10];
int main() {
    /*freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout);*/
    int x, idx = 0, i, j;
    while(1) {
        ReadInt(&x);
        if(x == -1) break;
        D[idx][0] = x;
        for(i = 1; i < 10; i++) {
            ReadInt(&x);
            D[idx][i] = x;
        }
        idx++;
    }
    while(ReadInt(&x)) {
        if(x == -1) break;
        A[0] = x;
        for(i = 1; i < 10; i++) {
            ReadInt(&x);
            A[i] = x;
        }
        for(i = 0; i < 10; i++) {
            ReadInt(&x);
            B[i] = x;
        }
        ReadInt(&x);
        int ans = 0;
        for(i = 0; i < idx; i++) {
            for(j = 0; j < 10; j++) {
                if(A[j] <= D[i][j] && D[i][j] <= B[j])
                    {}
                else    break;
            }
            if(j == 10)
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
