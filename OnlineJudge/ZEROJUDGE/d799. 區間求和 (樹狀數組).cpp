#include<stdio.h>
#define N 500001
long long sum[N];
long long c1[N], c2[N];
int A[N], lowbit[N], n;
int Input() { 
    char cha; 
    unsigned int x = 0; 
    while(cha = getchar()) 
        if(cha != ' ' && cha != '\n') break; 
    x = cha-48; 
    while(cha = getchar()) { 
        if(cha == ' ' || cha == '\n') break; 
        x = x*10 + cha-48; 
    } 
    return x; 
}
long long query(long long C[], int i) {
    long long sum = 0;
    while(i > 0) {
        sum += C[i];
        i -= lowbit[i];
    }
    return sum;
}
void update(long long C[], int i, long long k) {
    while(i <= n) {
        C[i] += k;
        i += lowbit[i];
    }
}
main() {
    int a, q, i, j, k;
    long long Ans;
    char v;
    for(a = 1; a < N; a++)
        lowbit[a] = a & (-a);
    scanf("%d", &n);
        for(a = 1; a <= n; a++)
            A[a] = Input();
        for(a = 1; a <= n; a++)
            sum[a] = sum[a-1] + A[a];
        scanf("%d", &q);
        getchar();
        while(q--) {
            v = getchar();
            if(v == '1') {
                i = Input(), j = Input(), k = Input();
                update(c1, i, k);
                update(c1, j+1, -k);
                update(c2, i, k*i);
                update(c2, j+1, -k*(j+1));
            }
            else {
                i = Input(), j = Input();
                Ans = sum[j] - sum[i-1];
                Ans += (j+1)*query(c1, j) - query(c2, j);
                Ans -=  i*query(c1, i-1) - query(c2, i-1);
                printf("%lld\n", Ans);
            }
        }
    return 0;
}
