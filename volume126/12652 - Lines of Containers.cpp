#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <algorithm>
using namespace std;

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

int R[262144], C[262144], A[512], B[512];
int swapSort(int A[], int n) {
    int visited[512] = {}, ret = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] != i && visited[i] == 0) {
            int cnt = 0;
            for (int j = i; visited[j] == 0; ) {
                visited[j] = 1, cnt++;
                j = A[j];
            }
            ret += cnt - 1;
        }
    }
    return ret;
}
int main() {
    int n, m, x;
    while (/* scanf("%d %d", &n, &m) == 2 && n */ ReadInt(&n)) {
        ReadInt(&m);
        vector<int> row[512], col[512];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ReadInt(&x);
                row[i].push_back(i * m + j + 1);
                col[j].push_back(i * m + j + 1);
                R[x] = i, C[x] = j;
            }
        }
        
        int err = 0;
        for (int i = 0; i < n && !err; i++) {
            int r = R[row[i][0]];
            for (int j = 0; j < row[i].size() && !err; j++) {
                if (R[row[i][j]] != r)
                    err = 1;
            }
            A[i] = r;
        }
        for (int i = 0; i < m && !err; i++) {
            int c = C[col[i][0]];
            for (int j = 0; j < col[i].size() && !err; j++) {
                if (C[col[i][j]] != c)
                    err = 1;
            }
            B[i] = c;
        }
        if (err)
            puts("*");
        else {
            printf("%d\n", swapSort(A, n) + swapSort(B, m));
        }
    }
    return 0;
}
/*
 2 2
 3 4
 1 2
 3 3
 9 2 4
 5 8 7
 6 1 3
 5 4
 13 15 14 16
 5 7 6 8
 9 11 10 12
 1 3 2 4
 17 19 18 20 
 1 4
 2 1 4 3
 */