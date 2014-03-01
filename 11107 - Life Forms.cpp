#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct SuffixArray {
    int sa[110005], h[110005], n;
    char str[110005];

    int w[110005], ta[110005], tb[110005]; // buffer
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
    }
};
SuffixArray SA;
int Sfrom[110005], Wlen[105], n, half;
char mark[105];
int check(int len, int printflag) {
    int i, j, k, cnt;
    for(i = n; i < SA.n; i++) {
        if(SA.h[i] >= len) {
            memset(mark, 0, sizeof(mark));
            j = i;
            cnt = 1;
            mark[Sfrom[SA.sa[i-1]]] = 1;
            while(j < SA.n && SA.h[j] >= len) {
                if(Sfrom[SA.sa[j]] != Sfrom[SA.sa[j]+len-1]) {
                    j++;break;
                }
                if(mark[Sfrom[SA.sa[j]]] == 0) {
                    mark[Sfrom[SA.sa[j]]] = 1;
                    cnt++;
                }
                j++;
            }
            if(cnt > half) {
                if(printflag) {
                    for(k = 0; k < len; k++)
                        putchar(SA.str[SA.sa[i]+k]);
                    puts("");
                } else {
                    return 1;
                }
            }
            i = j-1;
        }
    }
    return 0;
}
int main() {
    int i, first = 0;
    while(scanf("%d", &n) == 1 && n) {
        if(first)   puts("");
        first = 1;
        int m = 0;
        half = n/2; // > half
        int mxlen = 0;
        for(i = 0; i < n; i++) {
            scanf("%s", SA.str+m);
            int cnt = 0;
            while(SA.str[m])    Sfrom[m] = i, m++, cnt++;
            if(cnt > mxlen) mxlen = cnt;
            Wlen[i] = cnt;
            SA.str[m++] = '$';
            SA.str[m] = 0;
        }
        SA.str[m-1] = '\0';
        if(n == 1) {
            puts(SA.str);
            continue;
        }
        //puts(SA.str);
        SA.build();
        SA.build_h();
        int l = 1, r = mxlen;
        int res = 0;
        while(l <= r) {
            m = (l+r)/2;
            if(check(m, 0)) {
                l = m+1;
                if(m > res)
                    res = m;
            } else {
                r = m-1;
            }
        }
        if(res == 0)
            puts("?");
        else
            check(res, 1);
    }
    return 0;
}
