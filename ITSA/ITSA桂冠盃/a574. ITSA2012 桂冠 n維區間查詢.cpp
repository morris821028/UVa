#include <stdio.h>
#include <vector>
#define piece 51
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
vector<arr> P[2048];
int A[10], B[10], res = 0;
void dfs(int idx, int ptr) {
    int i;
    if(idx == 10) {
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
        dfs(idx+1, (ptr<<1) + i);
    }
}
int main() {
    int x, idx = 0, i, j;
    arr D;
    int ptr;
    while(1) {
        ReadInt(&x);
        if(x == -1) break;
        D.e[0] = x;
        ptr = x/piece;
        for(i = 1; i < 10; i++) {
            ReadInt(&x);
            D.e[i] = x;
            //if(i < 3)
            ptr = (ptr<<1) + x/piece;
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
        printf("%d\n", res);
    }
    return 0;
}
