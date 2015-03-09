/**********************************************************************************/
/*  Problem: d477 "古韵之同心锁" from vijos                                 */
/*  Language: CPP (3279 Bytes)                                                    */
/*  Result: AC(4ms, 260KB) judge by this@ZeroJudge                                */
/*  Author: morris1028 at 2013-01-25 19:45:00                                     */
/**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char s[10005], o1[] = "Immorta1";
    int m, n, p;
    int i, j, k;
    while(scanf("%s", s) == 1) {
        scanf("%d %d %d", &m, &n, &p);
        char a[10005], b[10005];
        int len = strlen(s);
        for(i = 0; i < m-1 && i < len; i++)
            a[i] = s[i];
        a[i] = '\0';
        for(i = m-1, j = 0; i < len; i++, j++)
            b[j] = s[i];
        b[j] = '\0';
        if(n == 1) {
            for(i = 0; s[i]; i++) {
                if(s[i] >= 'A' && s[i] <= 'Z')
                    s[i] = s[i]-'A'+'a';
                else if(s[i] >= 'a' && s[i] <= 'z')
                    s[i] = s[i]-'a'+'A';
                for(j = 0; j <= p; j++)
                    putchar(s[i]);
            }
            for(i = 0; o1[i]; i++) {
                for(j = 0; j <= p; j++)
                    putchar(o1[i]);
            }
            //puts("");
        } else if(n == 2) {
            int idx = 0;
            for(i = 0; a[i]; i++) {
                for(j = i, k = 0; b[k]; k++, j++)
                    if(a[j] != b[k])
                        break;
                if(b[k] == '\0') {
                    i = j-1;
                    continue;
                }
                a[idx++] = a[i];
            }
            a[idx] = '\0';
            char out[5000];
            idx = 0;
            for(i = 0; a[i]; i++) {
                if(a[i] == '1' && a[i+1] == '0' && a[i+2] == '1' && a[i+3] == '3') {
                    out[idx++] = 'h';
                    out[idx++] = 'h';
                    out[idx++] = '4';
                    out[idx++] = '7';
                    out[idx++] = '4';
                    out[idx++] = '2';
                    i += 3;
                    continue;
                }
                out[idx++] = a[i];
            }
            out[idx] = '\0';
            for(i = 0; out[i]; i++)
                for(j = 0; j <= p; j++)
                    putchar(out[i]);
            //puts("");
        } else {

            char out[10005];
            int idx = 0;
            for(i = 0; i < abs(n-m)-1; i++)
                out[idx++] = a[i];
            for(i = 0; b[i]; i++)
                out[idx++] = b[i];
            for(i = abs(n-m)-1; a[i]; i++)
                out[idx++] = a[i];
            for(i = 0; out[i]; i++)
                for(j = 0; j <= p; j++)
                    putchar(out[i]);
            if(m == 1) {
                for(i = 0; b[i]; i++)
                    for(j = 0; j <= p; j++)
                        putchar(b[i]);
                puts("");
            }
            puts("");
        }
    }
    return 0;
}
