#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    long long N, S, Q;
    while (scanf("%lld %lld %lld", &N, &S, &Q) == 3) {
        long long retK = 1LL<<60, retA = 0, retB = 0;
        for (int A = 0; A <= 33; A++) {
            for (int B = 0; B <= 100; B++) {
                if (((S + (S << A)) >> B) >= Q) {
                    long long pos = (N - 1) * S;
                    long long K = (pos + (pos << A)) >> B;
                    if (K < retK) {
                        retK = K;
                        retA = A;
                        retB = B;
                    }
                }
            }
        }
        retK += Q;
        printf("%lld %lld %lld\n", retK, retA, retB);
    }
    return 0;
}
/*
 20 3 5
 1024 7 1
*/