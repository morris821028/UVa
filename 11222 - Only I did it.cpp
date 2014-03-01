#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
    int t, Case = 0;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        printf("Case #%d:\n", ++Case);
        int A[3], B[3][1000];
        int mark[10001] = {};
        for(i = 0; i < 3; i++) {
            scanf("%d", &A[i]);
            for(j = 0; j < A[i]; j++) {
                scanf("%d", &B[i][j]);
                mark[B[i][j]]++;
            }
            sort(B[i], B[i]+A[i]);
        }
        int max = 0, solve[3];
        for(i = 0; i < 3; i++) {
            int tmp = 0;
            for(j = 0; j < A[i]; j++)
                if(mark[B[i][j]] == 1)
                    tmp++;
            if(tmp > max)
                max = tmp;
            solve[i] = tmp;
        }
        for(i = 0; i < 3; i++) {
            if(solve[i] == max) {
                printf("%d %d", i+1, solve[i]);
                for(j = 0; j < A[i]; j++)
                    if(mark[B[i][j]] == 1)
                        printf(" %d", B[i][j]);
                puts("");
            }
        }
    }
    return 0;
}
