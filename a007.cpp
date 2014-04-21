#include<stdio.h>
#include<stdlib.h>
int Pow(long long x, int n, long long mod) {
    long long Ans = 1, t = x;
    while(n) {
        if(n&1)
            Ans *= t, Ans %= mod;
        t *= t, t %= mod, n >>= 1;
    }
    return (int)Ans;
}
int JudgePrime(int n) {
    if(n == 2 || n == 3)    return 1;
    if(n == 1)    return 0;
    if(!(n&1))    return 0;
    int a, x, flag = 1, t;
    for(a = 0; a < 2; a++) {
        x = rand()%(n-4)+2;
        t = Pow(x, n-1, n);
        if(t != 1)    return 0;
    }
    return 1;
}
int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        if(JudgePrime(n))    puts("質數");
        else    puts("非質數");
    }
    return 0;
} 
