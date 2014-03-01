#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct SuffixArray {
    int sa[100005], h[100005], n;
    char str[100005];

    int w[100005], ta[100005], tb[100005]; // buffer
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
        for(k = 1, p = 1; p < n && k <= 1024; k *= 2, m = p) {
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
char q_str[100005];
int upper_search(int l, int r, int v, int idx, int upper, int lower) {
    static int m;
    while(l <= r) {
        m = (l+r)/2;
        if(SA.sa[m] + idx >= SA.n)
            l = m+1;
        else if(SA.str[SA.sa[m]+idx] < v)
            l = m+1;
        else if(SA.str[SA.sa[m]+idx] > v)
            r = m-1;
        else {
            if(m == upper)
                return m;
            if(SA.str[SA.sa[m+1]+idx] != v)
                return m;
            l = m+1;
        }
    }
    return -1;
}
int lower_search(int l, int r, int v, int idx, int upper, int lower) {
    static int m;
    while(l <= r) {
        m = (l+r)/2;
        if(SA.sa[m] + idx >= SA.n)
            l = m+1;
        else if(SA.str[SA.sa[m]+idx] < v)
            l = m+1;
        else if(SA.str[SA.sa[m]+idx] > v)
            r = m-1;
        else {
            if(m == lower)
                return m;
            if(SA.str[SA.sa[m-1]+idx] != v)
                return m;
            r = m-1;
        }
    }
    return -1;
}
int count() {
    int i, res = 0;
    int upper, lower, t_upper, t_lower;
    lower = 0, upper = SA.n-1;
    for(i = 0; q_str[i]; i++) {
        t_lower = lower_search(lower, upper, q_str[i], i, upper, lower);
        t_upper = upper_search(lower, upper, q_str[i], i, upper, lower);
        if(t_lower < 0 || t_upper < 0 || t_lower > t_upper)
            return 0;
        lower = t_lower;
        upper = t_upper;
    }
    return upper - lower + 1;
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    int q;
    while(testcase--) {
        scanf("%s", SA.str);
        SA.build();
        scanf("%d", &q);
        while(q--) {
            scanf("%s", q_str);
            int cnt = count();
            if(cnt)
                puts("y");
            else
                puts("n");
        }
        while(getchar() != '\n');
    }
    return 0;
}
