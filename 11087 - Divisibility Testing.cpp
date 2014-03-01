#include <stdio.h>
#include <algorithm>
using namespace std;
int t, n, k, cases = 0;
int A[100005], B[100005];
void RadixSort(int *A, int *B, int n) {
    int a, x, d, *T, C[256];
    for(x = 0; x < 4; x++) {
        d = x*8;
        for(a = 0; a < 256; a++)        C[a] = 0;
        for(a = 0; a < n; a++)        C[(A[a]>>d)&255]++;
        for(a = 1; a < 256; a++)    C[a] += C[a-1];
        for(a = n-1; a >= 0; a--)    B[--C[(A[a]>>d)&255]] = A[a];
        T = A, A = B, B = T;
    }
}
int main() {
    scanf("%d", &t);
    int i, j, k;
    while(t--) {
        scanf("%d %d", &n, &k);
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
            //ReadInt(&A[i]);
        //sort(A, A+n);
        RadixSort(A, B, n);
        long long ans = 0;
        if(n > 1 && A[0] == A[1] && (A[0]+A[1])%k == 0)
            ans++;
        for(i = 1, j = 0; i < n; i++) {
            if(A[i] != A[j]) {
                if(i+1 < n && A[i] == A[i+1] && (A[i]+A[i+1])%k == 0)
                    ans++;
                A[++j] = A[i];
            }
        }
        n = j+1;
        int cnt[505] = {};
        for(i = 0; i < n; i++) {
            j = A[i]%k;
            if(j < 0)   j += k;
            if(j)
                ans += cnt[k-j];
            else
                ans += cnt[0];
            cnt[j]++;
        }
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
