#include<stdio.h>
int A[200001];
main() {
    int n;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        int sum = 0, ans = 0;
        for(i = 0; i < n; i++) {
            sum += A[i];
            if(sum < 0)     sum = 0;
            if(sum > ans)   ans = sum;
        }
    }
    return 0;
}
