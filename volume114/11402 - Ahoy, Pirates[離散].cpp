#include <stdio.h>
#include <algorithm>
using namespace std;
char A[1048577];
int encode[1048577], one[2000];
int main() {
    int T, M, N, Q, t, a[1000], b[1000];
    int Case = 0, i, j, k, x, y;
    char str[100], op[1000][3];
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &M);
        N = 0;
        while(M--) {
            scanf("%d %s", &t, str);
            while(t--) {
                for(i = 0; str[i]; i++, N++)
                    A[N] = str[i]-'0';
            }
        }
        A[N] = '\0';
        scanf("%d", &Q);
        printf("Case %d:\n", ++Case);
        int QCase = 0, used[2000], ans;
        for(i = 0; i < Q; i++) {
            scanf("%s %d %d", op[i], &a[i], &b[i]);
            a[i]++, b[i]++;
            used[i<<1] = a[i]-1, used[i<<1|1] = b[i];
        }
        sort(used, used+(2*Q));
        encode[used[0]] = 0;
        for(i = 1, j = 0; i < 2*Q; i++) {
            if(used[j] != used[i]) {
                j++;
                used[j] = used[i];
                encode[used[j]] = j;
            }
        }
        for(i = 0; i < j; i++) {
            one[i] = 0;
            for(k = used[i]+1; k <= used[i+1]; k++)
                one[i] += A[k-1];
        }
        for(i = 0; i < Q; i++) {
            x = encode[a[i]-1], y = encode[b[i]]-1;
            if(op[i][0] == 'F') {
                for(j = x; j <= y; j++)
                    one[j] = used[j+1] - used[j];
            } else if(op[i][0] == 'E') {
                for(j = x; j <= y; j++)
                    one[j] = 0;
            } else if(op[i][0] == 'I') {
                for(j = x; j <= y; j++)
                    one[j] = used[j+1] - used[j] - one[j];
            } else {
                for(j = x, ans = 0; j <= y; j++)
                    ans += one[j];
                printf("Q%d: %d\n", ++QCase, ans);
            }
        }
    }
    return 0;
}
