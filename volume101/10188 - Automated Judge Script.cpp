#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
char A[105][150], B[105][150], bufA[10000], bufB[10000];
int n, m;
int AC() {
    if(n != m)  return 0;
    int i;
    for(i = 0; i < m; i++)
        if(strcmp(A[i], B[i]))
            return 0;
    return 1;
}
int PE() {
    int i, j, idxA = 0, idxB = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; A[i][j]; j++) {
            if(A[i][j] >= '0' && A[i][j] <= '9')
                bufA[idxA++] = A[i][j];
        }
    }
    for(i = 0; i < m; i++) {
        for(j = 0; B[i][j]; j++) {
            if(B[i][j] >= '0' && B[i][j] <= '9')
                bufB[idxB++] = B[i][j];
        }
    }
    bufA[idxA] = '\0';
    bufB[idxB] = '\0';
    return !strcmp(bufA, bufB);
}
int judge() {
    if(AC())    return 1;
    if(PE())    return 2;
    return 3;
}
int main() {
    int cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        cin.ignore(100, '\n');
        int i;
        for(i = 0; i < n; i++)
            gets(A[i]);
        scanf("%d", &m);
        cin.ignore(100, '\n');
        for(i = 0; i < m; i++)
            gets(B[i]);
        int flag = judge();
        printf("Run #%d: ", ++cases);
        if(flag == 1)
            puts("Accepted");
        else if(flag == 2)
            puts("Presentation Error");
        else
            puts("Wrong Answer");
    }
    return 0;
}
