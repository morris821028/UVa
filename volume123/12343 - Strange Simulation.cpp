#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

long long getLen(unsigned long long x) {
    int ret = 0;
    while (x)
        x >>= 1, ret++;
    return ret;
}

unsigned long long getHXor(long long n, long long len) {
//    long long ret = 0;
//    if (len > 1)    ret ^= 1LL<<(len-1);
//    if (len > 2)    ret ^= 1LL<<(len-2);
//    long long m = n;
//    for (long long i = len - 1; i >= 1; i--) {
//        m = n&((1LL<<(i))-1);
//        if (m&1) {
//            
//        } else {
//            ret ^= ((n>>i)&1LL)<<i;
//        }
//    }
//    if (n%4 == 1 || n%4 == 2)
//        ret |= 1;
//    return ret;
    if(n == 0)  return 0;
	if(n == 1)  return 1;
	if(n == 2)  return 0;
	if(n == 3)  return 3;
	long long r = (1LL<<(len-1)) | (1LL<<(len-2));
	if(n%4 == 1 || n%4 == 2)
        r |= 1;
	if(!(n&1))
        r^= (n - (n&1));
    return r;
}
int main() {
    int testcase, cases = 0;
    long long L, R;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%lld %lld", &L, &R);
        L--;
        long long alen = getLen(L), blen = getLen(R);
        long long Lv, Rv, ret;
        Lv = getHXor(L, alen);
        Rv = getHXor(R, blen);
        ret = (Lv<<(blen - alen))^Rv;
        assert(L >= 0 && R >= 0 && L < R);
        printf("Case %d: %llu\n", ++cases, ret);
    }
    return 0;
}

/*
 20
 1470348843 2529027115
 
 4
 1 4
 2 5
 1 2147483647
 7 12
 
 20
 812 1124
 972 1509
 802 1336
 919 1751
 671 1061
 551 1068
 463 664
 85 464
 68 326
 764 1214
 394 673
 995 1625
 49 645
 693 1630
 102 112
 955 974
 254 391
 364 415
 963 1673
 703 1071

 Case 1: 1124
 Case 2: 1
 Case 3: 1338
 Case 4: 1838
 Case 5: 1343
 Case 6: 98
 Case 7: 262
 Case 8: 128
 Case 9: 327
 Case 10: 1215
 Case 11: 3
 Case 12: 1991
 Case 13: 769
 Case 14: 823
 Case 15: 113
 Case 16: 116
 Case 17: 2
 Case 18: 0
 Case 19: 1927
 Case 20: 1406
 */
