#include <stdio.h>
#include <algorithm>
using namespace std;
struct ele {
    int a, b;
};
ele E[500], A[500];
bool cmp(ele a, ele b) {
    return a.b > b.b;
}
void sol(int n) {
    int i, j, e = 0;
    sort(A, A+n, cmp);
    for(i = 0; i < n; i++) {
        if(A[i].b < 0 || A[i].b >= n-i) {
            puts("Impossible");
            return;
        }
        for(j = i+1; A[i].b && j < n; j++) {
            E[e].a = A[i].a, E[e].b = A[j].a;
            A[j].b--;
            A[i].b--;
            e++;
        }
        sort(A+i+1, A+n, cmp);
    }
    printf("%d\n", e);
    for(i = 0; i < e; i++)
        printf("%d %d\n", E[i].a+1, E[i].b+1);
}
int main() {
    int n, i;
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            A[i].a = i, A[i].b = 3;
        sol(n);
    }
    return 0;
}
