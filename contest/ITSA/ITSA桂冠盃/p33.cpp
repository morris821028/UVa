#include <stdio.h>
#include <vector>
#define piece 11
using namespace std;
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
struct arr {
    char e[10];
};
vector<arr> P[1005];
int A[10], B[10], res = 0;
void dfs(int idx, int ptr) {
    int i;
    if(idx == 3) {
        for(vector<arr>::iterator it = P[ptr].begin();
            it != P[ptr].end(); it++) {
            for(i = 0; i < 10; i++) {
                if(!(A[i] <= it->e[i] && it->e[i] <= B[i]))
                    break;
            }
            if(i == 10)
                res++;
        }
        return;
    }
    int l = A[idx]/piece, r = B[idx]/piece;
    for(i = l; i <= r; i++) {
        dfs(idx+1, ptr*10 + i);
    }
}
int main() {
    freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);
    int x, idx = 0, i, j;
    arr D;
    int ptr;
    while(1) {
        ReadInt(&x);
        if(x == -1) break;
        D.e[0] = x;
        ptr = x/piece;

        //printf("%d", x/piece);
        for(i = 1; i < 10; i++) {
            ReadInt(&x);
            D.e[i] = x;
            if(i < 3)
                ptr = ptr*10 + x/piece;
          //  printf("%d", x/piece);
        }
        P[ptr].push_back(D);
        idx++;
    }
    while(ReadInt(&x)) {
        if(x == -1) break;
        A[0] = x;
        for(i = 1; i < 10; i++) {
            ReadInt(&x);
            A[i] = x;
        }
        for(i = 0; i < 10; i++) {
            ReadInt(&x);
            B[i] = x;
        }
        ReadInt(&x);
        res = 0;
        dfs(0, 0);
        /*for(i = 0; i < idx; i++) {
            for(j = 0; j < 10; j++) {
                if(A[j] <= D[i][j] && D[i][j] <= B[j])
                    {}
                else    break;
            }
            if(j == 10)
                ans++;
        }*/
        printf("%d\n", res);
    }
    return 0;
}
/*
98,22,82,100,34,58,57,77,55,97
56,52,58,84,54,14,83,87,67,12
27,81,57,2,27,73,20,53,8,78
89,44,3,87,3,64,85,37,9,73
45,88,49,19,73,100,16,72,29,88
94,84,28,94,12,25,37,15,40,92
11,59,92,89,2,87,24,60,39,82
34,46,53,35,2,41,77,92,27,82
60,49,20,75,6,57,0,22,28,54
59,41,78,32,64,37,62,100,47,81
-1
0,11,11,25,0,20,0,11,26,3
84,57,98,71,64,82,78,100,90,86
-1
0,0,0,0,0,0,0,0,0,0
100,100,100,100,100,100,100,100,100,100
-1
*/
