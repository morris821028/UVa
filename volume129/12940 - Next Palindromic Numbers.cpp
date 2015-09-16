#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    int m, n;
    char d[128];
    while (scanf("%d %s", &m, d) == 2) {
        n = (int) strlen(d);
        int A[128] = {}, B[128] = {};
        reverse(d, d+n);
        for (int i = 0; i < n; i++)
            A[i] = d[i] - '0', B[i] = A[i];
        for (int i = n-1, j = 0; i >= n/2; i--, j++)
            B[j] = B[i];
        int flag = 0;
        for (int i = n-1; i >= 0; i--) {
            if (B[i] != A[i]) {
                flag = B[i] > A[i];
                break;
            }
        }
        if (flag) {
            for (int i = n-1; i >= 0; i--)
                printf("%d", B[i]);
            puts("");
            m--;
        }
        for (int i = 0; i < m; i++) {
            A[n/2]++;
            for (int j = n/2; j <= n; j++) {
                if (A[j] >= 10) {
                    A[j+1] += A[j]/10;
                    A[j] %= 10;
                }
            }
            if (A[n])   n++;
            if (n%2) {
                for (int j = n-1; j > n/2; j--)
                    printf("%d", A[j]);
                printf("%d", A[n/2]);
                for (int j = n/2+1; j < n; j++)
                    printf("%d", A[j]);
            } else {
                for (int j = n-1; j >= n/2; j--)
                    printf("%d", A[j]);
                for (int j = n/2; j < n; j++)
                    printf("%d", A[j]);
            }
            puts("");
        }
    }
    return 0;
}