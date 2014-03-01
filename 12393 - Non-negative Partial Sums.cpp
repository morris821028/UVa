#include <stdio.h>
#define maxN 1048576<<1
int S[maxN], Q[maxN];
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
int main() {
    // using monotone queue (increasing)
    int n, x, i, j;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++) {
            ReadInt(&x);
            S[i+n] = S[i] = x;
        }
        int n2 = n<<1;
        for(i = 1; i < n2; i++)
            S[i] += S[i-1];
        int head = 0, tail = 0, ans = 0;
        for(i = 0; i < n2; i++) {
            while(head < tail && S[Q[tail-1]] >= S[i])
                tail--;
            Q[tail++] = i;
            if(i >= n && S[Q[head]] >= S[i-n])
                ans++;
            while(head < tail && Q[head] <= i-n)
                head++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
