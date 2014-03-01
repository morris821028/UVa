#include <stdio.h>
#include <string.h>
int peg[3], on, flag;
char m[100], bin[100];
int highbit;
void int2bin(int n) {
    memset(bin, 0, sizeof(bin));
    int i, j, tmp;
    int ml = strlen(m);
    for(i = 0; m[i]; i++)
        m[i] -= '0';
    for(i = 0; i < n; i++) {
        tmp = 0;
        for(j = 0; j < ml; j++) {
            tmp = tmp*10 + m[j];
            m[j] = tmp/2;
            tmp %= 2;
        }
        bin[i] = tmp;
    }
    highbit = n-1;
    while(highbit >= 0 && bin[highbit] == 0)
        highbit--;
}
void calc() {
    static int i;
    for(i = 0; i < on; i++) {
        if(bin[i] >= 2) {
            bin[i+1] += bin[i]/2;
            bin[i] %= 2;
        }
        while(bin[i] < 0)
            bin[i] += 2, bin[i+1]--;
    }
    highbit = on-1;
    while(highbit >= 0 && bin[highbit] == 0)
        highbit--;
}
void h(int n, int A, int B, int C) {
    if(flag)    return;
    if(highbit == -1) {
        if(on&1)
            printf("%d %d %d\n", peg[0], peg[2], peg[1]);
        else
            printf("%d %d %d\n", peg[0], peg[1], peg[2]);
        flag = 1;
    }
    if(n > 0) {
        if(highbit >= n-1 && n) {
            bin[n-1] = 0, bin[0]++;
            calc();
            peg[A] -= n-1, peg[B] += n-1;
        } else
            h(n-1, A, C, B);
        bin[0]--;
        calc();
        peg[A]--, peg[C]++;
        if(highbit >= n-1 && n) {
            bin[n-1] = 0, bin[0]++;
            calc();
            peg[B] -= n-1, peg[C] += n-1;
        } else
            h(n-1, B, A, C);
    }
}
int main() {
    while(scanf("%d %s", &on, m) == 2) {
        if(on == 0 && m[0] == '0')  break;
        peg[0] = on, peg[1] = peg[2] = flag = 0;
        int2bin(on);
        h(on, 0, 1, 2);
    }
    return 0;
}
