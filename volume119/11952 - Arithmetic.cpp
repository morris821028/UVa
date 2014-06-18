#include <stdio.h>
int flag;
long long ch(char s[], long long base) {
    long long sum = 0;
    int i;
    for(i = 0; s[i]; i++) {
        sum = s[i] - '0' + sum * base;
        if(s[i]-'0' >= base)
            flag = 1;
    }
    return sum;
}
int main() {
    int t, i;
    char A[9], B[9], C[9];
    scanf("%d", &t);
    while(t--) {
        scanf("%s + %s = %s", &A, &B, &C);
        long long a, b, c, d;
        a = 0, b = 0, c = 0, d = 1;
        for(a = 0; A[a]; a++) d &= A[a] == '1';
        for(b = 0; B[b]; b++) d &= B[b] == '1';
        for(c = 0; C[c]; c++) d &= C[c] == '1';
        if(d && a + b == c) {
            puts("1");
            continue;
        }
        for(i = 2; i <= 20; i++) {
            flag = 0;
            a = ch(A, i), b = ch(B, i), c = ch(C, i);
            if(a + b == c && flag == 0) {
                printf("%d\n", i);
                i = 500;
            }
        }
        if(i == 21)
            puts("0");
    }
    return 0;
}
