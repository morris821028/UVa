#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct SuffixArray {
    int sa[1005], h[1005], n;
    int w[1005], ta[1005], tb[1005];
    char str[1005];
    void sort(int *x, int *y, int m) {
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
    bool cmp(int *r, int a, int b, int l) {/*
        if(r[a] == r[b]) {
            if(a+l >= n || b+l >= n)
                return false;
            return r[a+l] == r[b+l];
        }
        return false;*/
        return r[a] == r[b] && r[a+l] == r[b+l];
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
    void build() {// x: rank, y: second key
        int i, k, m = 128, p;
        int *x = ta, *y = tb, *z;
        n = strlen(str);
        x[n] = 0;
        for(i = 0; i < n; i++)
            x[i] = str[i], y[i] = i;
        sort(x, y, m);
        for(k = 1, p = 1; p < n; k *= 2, m = p) {
            for(p = 0, i = n-k; i < n; i++)
                y[p++] = i;
            for(i = 0; i < n; i++) {
                if(sa[i] >= k) {
                    y[p++] = sa[i]-k;
                }
            }
            sort(x, y, m);
            z = x, x = y, y = z;
            for(i = 1, p = 1, x[sa[0]] = 0; i < n; i++)
                x[sa[i]] = cmp(y, sa[i-1], sa[i], k) ? p-1 : p++;
        }
        for(i = 0; i < n; i++)
            printf("%d ", sa[i]);
        puts("");
    }
};
int main() {
    SuffixArray in;
    int t;
    scanf("%d", &t);
    getchar();
    while(t--) {
        gets(in.str);
        in.build();
        in.build_h();
        int ans = 0, anst = 0;
        for(int i = 0; i < in.n; i++)
            ans = ans > in.h[i] ? ans : in.h[i];
        if(ans == 0) {
            puts("No repetitions found!");
        } else {
            for(int i = 0; i < in.n; i++) {
                if(ans == in.h[i]) {
                    for(int j = 0; j < ans; j++)
                        printf("%c", in.str[in.sa[i]+j]);
                    while(i < in.n && ans == in.h[i])
                        anst++, i++;
                    break;
                }
            }
            printf(" %d\n", anst+1);
        }
    }
    return 0;
}
