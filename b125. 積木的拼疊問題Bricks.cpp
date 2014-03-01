#include <cstdio>
#include <sstream>
#include <iostream>
using namespace std;
typedef struct {
    int v[100], bt;
} Bricks;
int test(Bricks A, Bricks B) {
    int shift, ans = 0, k;
    for(shift = 0; shift <= A.bt; shift++) {
        int comb[100] = {};
        for(k = 0; k < A.bt; k++)
            comb[k] = A.v[k];
        for(k = 0; k < B.bt; k++)
            comb[k+shift] += B.v[k];
        int w, h;
        w = B.bt+shift > A.bt ? B.bt+shift : A.bt;
        h = comb[0];
        for(k = 0; k < w; k++)
            if(h != comb[k])
                break;
        if(k == w) {
            if(w*h > ans)
                ans = w*h;
        }
        for(k = 0; k < B.bt; k++)
            comb[k+shift] += B.v[B.bt-k-1]-B.v[k];
        h = comb[0];
        for(k = 0; k < w; k++)
            if(h != comb[k])
                break;
        if(k == w) {
            if(w*h > ans)
                ans = w*h;
        }
    }
    return ans;
}
Bricks rotate(Bricks A) {
    Bricks B;
    int can = 0, i, j;
    for(i = 1; i < A.bt; i++)
        if(A.v[i] < A.v[i-1])
            break;
    if(i == A.bt)   can = 1;
    for(i = 1; i < A.bt; i++)
        if(A.v[i] > A.v[i-1])
            break;
    if(i == A.bt)   can = 2;
    if(!can) {
        B.bt = -1;
        return B;
    }
    B.bt = A.v[A.bt-1] > A.v[0] ? A.v[A.bt-1] : A.v[0];
    for(i = 0; i < B.bt; i++) {
        B.v[i] = 0;
        for(j = 0; j < A.bt; j++)
            if(A.v[j] > i)
                B.v[i]++;
    }
    return B;
}
int main() {
    int n;
    int i, j, k;
    while(scanf("%d", &n) == 1) {
        getchar();
        string line;
        Bricks D[100];
        for(i = 0; i < n; i++) {
            getline(cin, line);
            stringstream sin(line);
            D[i].bt = 0;
            while(sin>> D[i].v[D[i].bt])
                D[i].bt++;
        }
        int ans = 0;
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                int tmp = test(D[i], D[j]);
                ans = tmp > ans ? tmp : ans;
                test(D[j], D[i]);
                ans = tmp > ans ? tmp : ans;
                Bricks Ra, Rb;
                Ra = rotate(D[i]);
                Rb = rotate(D[j]);
                if(Ra.bt > 0) {
                    tmp = test(D[j], Ra);
                    ans = tmp > ans ? tmp : ans;
                    tmp = test(Ra, D[j]);
                    ans = tmp > ans ? tmp : ans;
                }
                if(Rb.bt > 0) {
                    tmp = test(D[i], Rb);
                    ans = tmp > ans ? tmp : ans;
                    tmp = test(Rb, D[i]);
                    ans = tmp > ans ? tmp : ans;
                }
                if(Ra.bt > 0 && Rb.bt > 0) {
                    tmp = test(Ra, Rb);
                    ans = tmp > ans ? tmp : ans;
                    tmp = test(Rb, Ra);
                    ans = tmp > ans ? tmp : ans;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
/*
10
1 1 1 3 7
5 7 8 9 2
1 2 3 4 5
1 1 2 2 2 2 3 3 5 6
3 3 4 4 4 4
1 1 1 1 1 1 1 1 1 1 1 1 1 1 2
10 2
2 3 5
10 11 15
1 10 30
*/
