#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
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
    int n, i, j, k, A[1000], table[1000];
    while(ReadInt(&n) == 1) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++)
                ReadInt(&A[j]);
            sort(A, A+n);
            if(i == 0) {
                for(j = 0; j < n; j++)
                    table[j] = A[j];
                continue;
            }
            priority_queue<int> pQ;
            for(j = 0; j < n; j++)
                pQ.push(table[j]+A[0]);
            for(j = 0; j < n; j++) {
                for(k = 1; k < n; k++) {
                    if(table[j]+A[k] < pQ.top()) {
                        pQ.pop();
                        pQ.push(table[j]+A[k]);
                    } else
                        break;
                }
            }
            j = n-1;
            while(!pQ.empty())
                table[j--] = pQ.top(), pQ.pop();
        }
        printf("%d", table[0]);
        for(i = 1; i < n; i++)
            printf(" %d", table[i]);
        puts("");
    }
    return 0;
}
