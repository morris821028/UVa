#include <stdio.h>
#include <string.h>

long long plus[2][80005]; // shift 40000
long long minus[2][80005]; // shift 40000
void solve(int n, int f, int A[]) {
    int i, j, k, roll = 0, L, R;
    memset(plus, 0, sizeof(plus));
    memset(minus, 0, sizeof(minus));
    plus[roll][A[0]+40000] = 1;
    minus[roll][-A[0]+40000] = 1;
    L = -A[0]+40000;
    R = A[0]+40000;
    for(i = 1; i < n; i++) {
        memset(plus[1-roll], 0, sizeof(plus[0]));
        memset(minus[1-roll], 0, sizeof(minus[0]));
        for(j = L; j <= R; j++) {
            if(plus[roll][j] || minus[roll][j]) {
                k = j + A[i];
                plus[1-roll][k] |= plus[roll][j]|(1LL<<i);
                minus[1-roll][k] |= minus[roll][j];
                k = j - A[i];
                plus[1-roll][k] |= plus[roll][j];
                minus[1-roll][k] |= minus[roll][j]|(1LL<<i);
            }
        }
        L -= A[i];
        R += A[i];
        roll = 1-roll;
    }
    long long a = plus[roll][f+40000], b = minus[roll][f+40000];
    if(a == 0 && b == 0) {
        puts("*");
        return;
    }
    for(i = 0; i < n; i++) {
        if((a>>i)&1) {
            if((b>>i)&1)
                putchar('?');
            else
                putchar('+');
        } else
            putchar('-');
    }
    puts("");
}
int main() {
    int n, f, A[50], i;
    while(scanf("%d %d", &n, &f) == 2 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        solve(n, f, A);
    }
    return 0;
}
