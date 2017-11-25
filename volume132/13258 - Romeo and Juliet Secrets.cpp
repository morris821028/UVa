#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 131072;
struct SuffixArray {
    int sa[MAXN], h[MAXN], n;
    int w[MAXN], ta[MAXN], tb[MAXN];
    char str[MAXN];
    void sort(int *x, int *y, int m) {
        for (int i = 0; i < m; i++) w[i] = 0;
        for (int i = 0; i < n; i++) w[x[y[i]]]++;
        for (int i = 1; i < m; i++) w[i] += w[i-1];
        for (int i = n-1; i >= 0; i--)  sa[--w[x[y[i]]]] = y[i];
    }
    bool cmp(int *r, int a, int b, int l) {
        if (r[a] == r[b]) {
            if (a+l >= n || b+l >= n)
                return false;
            return r[a+l] == r[b+l];
        }
        return false;
    }
    void buildH() {
        for (int i = 0; i < n; i++)  ta[sa[i]] = i;
        for (int i = 0; i < n; i++) {
            if(ta[i] == 0) {
                h[ta[i]] = 0;
                continue;
            }
            int k;
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
        int m = 128;
        int *x = ta, *y = tb, *z;
        n = (int) strlen(str);
        x[n] = 0;
        for (int i = 0; i < n; i++)
            x[i] = str[i], y[i] = i;
        sort(x, y, m);
        for (int k = 1, p = 1, i; p < n; k *= 2, m = p) {
            for (p = 0, i = n-k; i < n; i++)
                y[p++] = i;
            for (i = 0; i < n; i++) {
                if(sa[i] >= k) {
                    y[p++] = sa[i]-k;
                }
            }
            sort(x, y, m);
            z = x, x = y, y = z;
            for (i = 1, p = 1, x[sa[0]] = 0; i < n; i++)
                x[sa[i]] = cmp(y, sa[i-1], sa[i], k) ? p-1 : p++;
        }
    }
};
SuffixArray in;
void allPosMatchLen(char T[], int tLen, char W[], int wLen, int sa[], int h[], int ret[]) {
    int pos = 0;
//    printf("%s --------\n", W);
    for (int i = 0; i < tLen; i++) {
        if (h[i] < pos) pos = h[i];
        while (pos < wLen && W[pos] == T[sa[i]+pos])
            pos++;
//        while (pos > 0 && W[pos-1] != T[sa[i]+pos-1])
//            pos--;
        ret[sa[i]] = pos;
//        printf("%s %d %d\n", in.str + in.sa[i], in.h[i], pos);
    }
}
int main() {
    int testcase;
    static char T[MAXN], W[MAXN];
    static int pLen[MAXN], sLen[MAXN];
    int K;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s %s %d", T, W, &K);
        
        int tLen = (int) strlen(T), wLen = (int) strlen(W);
        
        strcpy(in.str, T);
        in.build(), in.buildH();
        allPosMatchLen(T, tLen, W, wLen, in.sa, in.h, pLen);
        
        
        reverse(in.str, in.str+in.n);
        reverse(W, W+wLen);
        reverse(T, T+tLen);
        in.build(), in.buildH();
        allPosMatchLen(T, tLen, W, wLen, in.sa, in.h, sLen);
        reverse(sLen, sLen+tLen);
        
//        reverse(T, T+tLen);
//        printf("%s\n", T);
//        for (int i = 0; i < tLen; i++)
//            printf("%d", pLen[i]);
//        puts("");
//        for (int i = 0; i < tLen; i++)
//            printf("%d", sLen[i]);
//        puts("");
        
        int ret = 0;
        for (int i = 0; i+wLen <= tLen; i++) {
            int match = pLen[i] + sLen[i+wLen-1];
            if (match >= wLen - K)
                ret++;
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 3
 oxwmeorozkowhereforeartthouromeo
 romeo
 2
 
 abcabcabcabcabc
 aba
 1
 abcabcabcabcabc
 acb
 2
*/
