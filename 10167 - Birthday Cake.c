#include <stdio.h>
int x[100], y[100];
int test(int A, int B, int N) {
    static int i, pos, neg, tmp;
    pos = 0, neg = 0;
    for(i = 2*N-1; i >= 0; i--) {
        tmp = A*x[i] + B*y[i];
        if(tmp < 0)
            neg ++;
        else if(tmp > 0)
            pos ++;
        else
            return 0;
    }
    return pos == neg;
}
void find(int N) {
    int A, B;
    while(1) {
        A = rand()%1001-500;
        B = rand()%1001-500;
        if(test(A, B, N)) {
            printf("%d %d\n", A, B);
            break;
        }
    }
}
int main() {
    int N, i;
    while(scanf("%d", &N) == 1 && N) {
        for(i = 2*N-1; i >= 0; i--)
            scanf("%d %d", &x[i], &y[i]);
        find(N);
    }
    return 0;
}
