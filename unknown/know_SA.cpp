#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct SuffixArray {
    int sa[1005], h[1005], n;
    char str[1005];

    int w[1005], ta[1005], tb[1005]; // buffer
    void sort(int *x, int *y, int m) { // radix sort
        static int i;
        for(i = 0; i < m; i++)
            w[i] = 0;
        for(i = 0; i < n; i++)
            w[x[y[i]]]++;
        for(i = 1; i < m; i++)
            w[i] += w[i-1];
        for(i = n-1; i >= 0; i--)
            sa[--w[x[y[i]]]] = y[i];
    }
    bool cmp(int *r, int a, int b, int l) {
        if(r[a] == r[b]) {
            if(a+l >= n || b+l >= n)
                return false;
            return r[a+l] == r[b+l];
        }
        return false;
    }
    void build_h() {
        int i, j, k;
        for(i = 0; i < n; i++)  ta[sa[i]] = i;
        for(i = 0; i < n; i++) {
            if(ta[i] == 0) {
                h[ta[i]] = 0;
                continue;
            }
            if(i == 0 || h[ta[i-1]] <= 1)
                k = 0;
            else
                k = h[ta[i-1]]-1;
            while(str[sa[ta[i]-1]+k] == str[sa[ta[i]]+k])
                k++;
            h[ta[i]] = k;
        }
    }
    void build() {// x: rank, y: second key(array index)
        int i, k, m = 128, p;
        int *x = ta, *y = tb, *z;
        n = strlen(str);
        x[n] = 0;
        for(i = 0; i < n; i++)
            x[i] = str[i]-'a', y[i] = i;
        sort(x, y, m);
        for(i = 0; i < n; i++)
            printf("%d ", sa[i]);
        puts("sa");
        for(k = 1, p = 1; p < n; k *= 2, m = p) {
            for(p = 0, i = n-k; i < n; i++)
                y[p++] = i;
            for(i = 0; i < n; i++) {
                if(sa[i] >= k) {
                    y[p++] = sa[i]-k;
                }
            }
            for(i = 0; i < n; i++)
                printf("%d ", x[y[i]]);
            puts("second key");
            for(i = 0; i < n; i++)
                printf("%d ", y[i]);
            puts("y");
            sort(x, y, m);
            z = x, x = y, y = z;

            for(i = 0; i < n; i++)
                printf("%d ", sa[i]);
            puts("sa");
            for(i = 1, p = 1, x[sa[0]] = 0; i < n; i++)
                x[sa[i]] = cmp(y, sa[i-1], sa[i], k) ? p-1 : p++;
            for(i = 0; i < n; i++)
                printf("%d ", x[i]);
            puts("x");
        }
    }
};

int main() {
    SuffixArray SA;
    while(gets(SA.str)) {
        SA.build();
    }
    return 0;
}
