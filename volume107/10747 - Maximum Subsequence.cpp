#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
using namespace std;
bool cmp(int a, int b) {
    if(abs(a) != abs(b))
        return abs(a) > abs(b);
    return a > b;
}
int n, m, A[10000];
int i, j;
int P[10000], Q[10000], R[10000], pn, qn, rn;
int final_res;
double LOGV[10000];
double sigma1, sigma2;
int sol_plus() { // max positive integer
    int cnt = 0, res = 0;
    int pidx = 0, qidx = 0;
    while(pidx+1 < pn && qidx+1 < qn) {
        if(cnt == m || cnt == m-1)
            break;
        if(pidx+1 < pn && qidx+1 < qn && P[pidx]*P[pidx+1] >= Q[qidx]*Q[qidx+1])
            cnt += 2, res += P[pidx]+P[pidx+1],
            sigma1 += LOGV[P[pidx]]+LOGV[P[pidx+1]], pidx += 2;
        else
            cnt += 2, res += Q[qidx]+Q[qidx+1],
            sigma1 += LOGV[-Q[qidx]]+LOGV[-Q[qidx+1]], qidx += 2;
    }
    while(pidx+1 < pn) {
        if(cnt == m || cnt == m-1)
            break;
        cnt += 2, res += P[pidx]+P[pidx+1],
        sigma1 += LOGV[P[pidx]]+LOGV[P[pidx+1]], pidx += 2;
    }
    while(qidx+1 < qn) {
        if(cnt == m || cnt == m-1)
            break;
        cnt += 2, res += Q[qidx]+Q[qidx+1],
        sigma1 += LOGV[-Q[qidx]]+LOGV[-Q[qidx+1]], qidx += 2;
    }
    if(cnt == m) {
        final_res = res;
        return 1;
    } else {
        if(pidx < pn && cnt+1 == m) {
            res += P[pidx];
            sigma1 += LOGV[P[pidx]];
            final_res = res;
            return 1;
        }
        return 0;
    }
}
int sol_plus2() { // max positive integer remove first
    if(pn == 0) return 0;
    //puts("plus2 process");
    int cnt = 1, res = P[0];
    int pidx = 1, qidx = 0;
    while(pidx+1 < pn && qidx+1 < qn) {
        if(cnt == m || cnt == m-1)
            break;
        if(pidx+1 < pn && qidx+1 < qn && P[pidx]*P[pidx+1] >= Q[qidx]*Q[qidx+1])
            cnt += 2, res += P[pidx]+P[pidx+1],
            sigma2 += LOGV[P[pidx]]+LOGV[P[pidx+1]], pidx += 2;
        else
            cnt += 2, res += Q[qidx]+Q[qidx+1],
            sigma2 += LOGV[-Q[qidx]]+LOGV[-Q[qidx+1]], qidx += 2;
    }
    while(pidx+1 < pn) {
        if(cnt == m || cnt == m-1)
            break;
        cnt += 2, res += P[pidx]+P[pidx+1],
        sigma2 += LOGV[P[pidx]]+LOGV[P[pidx+1]], pidx += 2;
    }
    while(qidx+1 < qn) {
        if(cnt == m || cnt == m-1)
            break;
        cnt += 2, res += Q[qidx]+Q[qidx+1],
        sigma2 += LOGV[-Q[qidx]]+LOGV[-Q[qidx+1]], qidx += 2;
    }
    if(cnt == m) {
        final_res = res;
        return 1;
    } else {
        if(pidx < pn && cnt+1 == m) {
            res += P[pidx];
            sigma2 += LOGV[P[pidx]];
            final_res = res;
            return 1;
        }
        return 0;
    }
}
int sol_zero() { // equal zero
    //puts("zero process");
    if(A[n-1] != 0)
        return 0;
    int cnt = 0, res = 0;
    pn = 0, qn = 0, rn = 0;
    for(i = 0; i < n; i++) {
        if(A[i] > 0)
            P[pn++] = A[i];
        else if(A[i] < 0)
            Q[qn++] = A[i];
        else
            R[rn++] = A[i];
    }
    cnt = 1, rn--;
    int pidx = 0;
    while(pidx < pn && cnt < m)
        cnt++, res += P[pidx], pidx++;
    while(rn-1 >= 0 && cnt < m)
        cnt++, rn--;
    while(qn-1 >= 0 && cnt < m)
        cnt++, res += Q[qn-1], qn--;
    if(cnt == m) {
        final_res = res;
        return 1;
    }
    return 0;
}
int sol_minus() {
    //puts("minus process");
    int res = 0, cnt = m;
    for(i = n-1, cnt = m-1; cnt >= 0; i--, cnt--) {
        res += A[i];
    }
    final_res = res;
    return 1;
}
int main() {
    LOGV[0] = 0;
    for(i = 1; i <= 10000; i++)
        LOGV[i] = log(i);
    while(scanf("%d %d", &n, &m) == 2 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        sort(A, A+n, cmp);
        pn = 0, qn = 0;
        for(i = 0; i < n; i++) {
            if(A[i] > 0)
                P[pn++] = A[i];
            else if(A[i] < 0)
                Q[qn++] = A[i];
        }
        sigma1 = 0;
        sigma2 = 0;
        int flag1 = sol_plus();
        int flag2 = sol_plus2();
        //printf("%lf %lf %d %d\n", sigma1, sigma2, flag1, flag2);
        if(flag1 == 0 && flag2 == 0)
            !sol_zero() && sol_minus();
        else {
            if(flag2 == 0 || sigma1 > sigma2)
                sol_plus();
            else
                sol_plus2();
        }
        printf("%d\n", final_res);
    }
    return 0;
}
/*
4 4
1 2 3 4
4 1
1 2 3 4
4 2
4 4 -4 -4
8 5
1 -1 -1 0 1 -3 -1 -1
100 29
-98 -52 47 50 3 87 96 30 -87 -70 55 98 -42 -68 -26 93 -72 -75 -37 -63 94 63 90 -6 -58 -51 0 72 -70 73 -33 64 -85 -37 40 -56 43 -90 84 30 -52 1 94 -48 57 -44 -63 -45 -14 -16 15 3 -13 43 -31 52 42 50 -17 12 -9 -28 -7 22 59 34 -59 -7 -89 46 98 -21 91 48 -88 -49 22 59 97 42 11 -65 -48 -4 -14 34 -18 90 52 94 -32 -16 21 -16 -10 -21 -19 -96 57 -62
*/
