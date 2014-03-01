#include <stdio.h>

int main() {
    int t, k, i, j, s;
    unsigned C[50001];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &k);
        for(i = 1; i <= k; i++)
            C[i] = 0;
        for(i = 1; i <= k; i++) {
            j = i;
            while(j <= k) {
                C[j]++;
                j += j&(-j);
            }
        }
        int l, r, m, sum1, sum2;
        for(i = 1; i <= k; i++) {
            scanf("%d", &s);
            s++;
            l = 1, r = k;
            if(i != 1)
                putchar(' ');
            while(l <= r) {
                m = (l+r)>>1;
                j = m, sum1 = 0;
                while(j > 0)    sum1 += C[j], j -= j&(-j);

                if(sum1 == s) {
                    j = m-1, sum2 = 0;
                    while(j > 0)    sum2 += C[j], j -= j&(-j);
                    if(sum1 == sum2+1)
                        break;
                    else
                        r = m-1;
                } else if(sum1 > s)
                    r = m-1;
                else
                    l = m+1;
            }
            printf("%d", m);
            j = m;
            while(j <= k) {
                C[j]--;
                j += j&(-j);
            }
        }
        puts("");
    }
    return 0;
}
