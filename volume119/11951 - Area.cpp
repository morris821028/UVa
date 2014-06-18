#include <stdio.h>
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int t, N, M, K;
    int g[105][105];
    int cases = 0;
    int i, j, k, l;
    //scanf("%d", &t);
    ReadInt(&t);
    while(t--) {
        //scanf("%d %d %d", &N, &M, &K);
        ReadInt(&N);
        ReadInt(&M);
        ReadInt(&K);
        for(i = 0; i < N; i++)
            for(j = 0; j < M; j++)
                //scanf("%d", &g[i][j]);
                ReadInt(&g[i][j]);
        int mx = 0, mxv = 0;
        long long tmp;
        int cnt = 0;
        for(i = 0; i < N; i++) {
            int sum[105] = {};
            for(j = i; j < N; j++) {
                for(k = 0, l = 0; k < M; k++) {
                    sum[k] += g[j][k];
                    if(k == 0)  tmp = 0;
                    tmp += sum[k];
                    while(tmp > K)
                        tmp -= sum[l++];
                    if((j-i+1)*(k-l+1) > mx)
                        mx = (j-i+1)*(k-l+1), mxv = K;
                    if((j-i+1)*(k-l+1) == mx && tmp < mxv)
                        mxv = tmp;
                }
            }
        }
        printf("Case #%d: %d %d\n", ++cases, mx, mxv);
    }
    return 0;
}
