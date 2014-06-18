#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
/*
bool dfs(int m1[7], int m2[7], int idx){
if(idx == 0){
return m1[0]>=m2[0];
}
if(m2[idx]>m1[idx])
return 0;
m1[idx]-=m2[idx];
m1[idx-1] = m1[idx]*4;
return dfs(m1,m2,idx-1);
}

bool check(int k, int m2[7]){
int m1[7]={};
int val[7]={1,2,4,8,16,32,64};
int rx = k, ry = k, prex = 0, prey = 0;
for(int fh1=6;fh1>=0;fh1--){
m1[fh1] += (rx/val[fh1])*prey+(ry/val[fh1])*prex + (rx/val[fh1])*(ry/val[fh1]);
rx %= val[fh1];
ry %= val[fh1];
}
return dfs(m1,m2,6);
}*/
void check(int A[], int H, int W) {
    //printf("%d %d\n", H, W);
    int i, j;
    int hh = 0, ww, rr;
    int size;
    /*for(i = 0; i < 7; i++)
        printf("%d ", A[i]);
    puts("");*/
    while(1) {
        for(j = 6; j >= 0; j--) {
            for(i = j; i >= 0; i--)
                if(A[i])
                    break;
            if(i == -1)
                return ;
            size = 1<<i;
            if(hh + size > H)
                continue;
            ww = min(W/size, A[i]);
            if(ww == 0)
                continue;
            A[i] -= ww;
            rr = W - ww*size;
            check(A, rr, size);
            hh += size;
            break;
        }
        if(j == -1)
            return ;
    }
    return ;
}
int main() {
    int i;
    int A[7];
    while(scanf("%d", &A[0]) == 1 && A[0] >= 0) {
        int sum = 0;
        for(i = 1; i < 7; i++)
            scanf("%d", &A[i]);
        for(i = 0; i < 7; i++)
            sum += A[i] * (1<<i)*(1<<i);
        int K = (int)sqrt(sum);
        i = 0;
        int C[7];
        while(1) {
            for(i = 0; i < 7; i++)
                C[i] = A[i];
            check(C, K, K);
            for(i = 0; i < 7; i++)
                if(C[i])
                    break;
            if(i == 7)  break;
            K++;
            if(K > 30000)
                break;
        }
        printf("%d\n", K);
    }
    return 0;
}
