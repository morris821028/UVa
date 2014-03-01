#include <stdio.h>
#include <algorithm>
using namespace std;
struct E {
    int x, dir;
};
struct F {
    int x, dir, idx;
};
bool cmp(E a, E b) {
    return a.x < b.x;
}
bool cmp2(F a, F b) {
    return a.idx < b.idx;
}
int main() {
    int testcase, L, T, n;
    int x, cases = 0, i;
    char s[50];
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d %d", &L, &T, &n);
        E A[10005], B[10005];
        for(i = 0; i < n; i++) {
            scanf("%d %s", &x, s);
            if(s[0] == 'L') {
                A[i].x = x, A[i].dir = i; // A.dir as index
                B[i].x = x-T, B[i].dir = 0;
            } else {
                A[i].x = x, A[i].dir = i; // A.dir as index
                B[i].x = x+T, B[i].dir = 1;
            }
        }
        sort(A, A+n, cmp);
        sort(B, B+n, cmp);
        F ret[10005];
        for(i = 0; i < n; i++) {
            ret[i].x = B[i].x;
            ret[i].dir = B[i].dir;
            ret[i].idx = A[i].dir;
            if(i > 0 && B[i].x == B[i-1].x)
                ret[i].dir = -1;
            if(i+1 < n && B[i].x == B[i+1].x)
                ret[i].dir = -1;
        }
        sort(ret, ret+n, cmp2);
        printf("Case #%d:\n", ++cases);
        for(i = 0; i < n; i++) {

            if(ret[i].x < 0 || ret[i].x > L)
                puts("Fell off");
            else {
                if(ret[i].dir == -1)
                    printf("%d Turning\n", ret[i].x);
                else
                    printf("%d %c\n", ret[i].x, ret[i].dir ? 'R' : 'L');
            }
        }
        puts("");
    }
    return 0;
}
