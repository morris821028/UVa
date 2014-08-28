#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;


int main() {
    int testcase, cases = 0;
    char s[1024];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s", s + 1);
        printf("Case %d:", ++cases);
        s[0] = 'L';
        int A[20], slen = (int)strlen(s);
        for (int m = 1, n = 20; m <= 20; m++) { // C(n, m)
            int v[20] = {}; // generating combination
            for (int i = 0; i < n - m; i++)
                v[i] = 1;
            sort(v, v+n);
            do {
                int cn = 0;
                for (int i = 0; i < 20; i++) {
                    if (!v[i])
                        A[cn++] = i + 1;
                }
                // dp
                int ok = 1;
                for (int i = 1; i < slen; i++) {
                    int d = 'L';
                    for (int j = 0; j < cn && i - A[j] >= 0; j++) {
                        if (s[i - A[j]] == 'L') {
                            d = 'W';
                            break;
                        }
                    }
                    if (d != s[i]) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) {
                    for (int i = 0; i < cn; i++)
                        printf(" %d", A[i]);
                    puts("");
                    m = 100; // break outer loop
                    break;
                }
            } while (next_permutation(v, v + n));
        }
    }
    return 0;
}

/*
 3
 WWLWWL
 WWWW
 WLW
 
 Case 1: 1 2
 Case 2: 1 2 3 4
 Case 3: 1
 */