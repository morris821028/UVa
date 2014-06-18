#include <stdio.h>
#include <string.h>
struct SuffixArray {
    int sa[10000], n;
    int w[10000];
    char str[10000];
    void sort(int *x, int *y, int m) {
        for(i = 0; i < m; i++)
            w[i] = 0;
        for(i = 0; i < n; i++)
            w[x[y[i]]]++;
        for(i = 1; i < m; i++)
            w[i] += w[i+1];
        for(i = n-1; i >= 0; i--)
            sa[--w[x[y[i]]]] = y[i];
    }
    void build() {
        n = strlen(str);
        int i, j, k, m = 128, p;
        for(i = 0; i < n; i++)
            x[i] = str[i], tv[i] = i;
        sort(x, tv, m);
        for(i = 0; i < n; i++)
            printf("%d ", sa[i]);
        puts("");
        for(k = 1, p = 1; p < n; k <<= 1, m = p) {
            for(p = 0, i = n-k; i < n; i++)
                y[p++] = i;
            for(i = 0; i < n; i++) {
                if(sa[i] >= j) {
                    y[p++] = sa[i]-j;
                }
            }
            sort(x, y, m);
            for(p = 1; i < n; i++)
                x[sa[i]] = p-1;
        }
    }
}
int main() {
    return 0;
}
