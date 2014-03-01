#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
int A[105], goal, m, flag, n;
int used[105] = {}, B[105];
int dfs(int idx, int st, int sum, int tm) {
    if(sum == goal) {
        if(tm+1 == m) return 1;
        if(dfs(0, 1, 0, tm+1))
            return 1;
        return 0;
    }
    if(st == 1) {
        int i;
        for(i = 0; used[i]; i++);
        used[i] = 1;
        if(dfs(i+1, 0, A[i], tm))
            return 1;
        used[i] = 0;
    } else {
        int i;
        for(i = idx; i < n; i++) {
            if(used[i] == 0 && sum+A[i] <= goal && sum+B[i] >= goal) {
                if(i && A[i] == A[i-1] && used[i-1] == 0)
                    continue;
                used[i] = 1;
                if(dfs(i+1, 0, sum+A[i], tm))
                    return 1;
                used[i] = 0;
                if(sum+A[i] == goal)
                    return 0;
            }
        }
    }
    return 0;
}
int main() {
    int i;
    while(scanf("%d", &n) == 1 && n) {
        int sum = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            sum += A[i];
            used[i] = 0;
        }
        sort(A, A+n, greater<int>());
        for(i = n-1, B[n] = 0; i >= 0; i--)
            B[i] = B[i+1]+A[i];
        int L = A[0];
        flag = 0;
        for(; L <= sum/2; L++) {
            if(sum%L)   continue;
            goal = L;
            m = sum/L;
            flag = dfs(0,1,0,0);
                //printf("try %d\n", goal);
            if(flag)    break;
        }
        if(!flag)   goal = sum;
        printf("%d\n", goal);
    }
    return 0;
}
