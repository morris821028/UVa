#include <stdio.h>
#include <algorithm>
using namespace std;
struct H {
    int c, p;
};
H D[200005];
int main() {
    int N, K, M;
    int L[51] = {}, R[51] = {};
    int i, j;
    scanf("%d %d %d", &N, &K, &M);
    for(i = 0; i < N; i++) {
        scanf("%d %d", &D[i].c, &D[i].p);
        R[D[i].c]++;
    }
    int res = 0;
    for(i = 0; i < N; i++) {
        if(D[i].p < M) {
            for(j = 0; j < K; j++) {
                //if(L[j]*R[j])
                  //  printf("%d %d %d\n", i, j, L[j]*R[j]);
                res += L[j]*R[j];
            }
        }
        L[D[i].c]++, R[D[i].c]--;
    }
    printf("%d\n", res);
    return 0;
}
