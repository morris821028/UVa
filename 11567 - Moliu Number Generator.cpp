#include <stdio.h>
long long check(long long n) {
    if(n == 3)  return 2;
    if(n-1 == 0)    return n-1;
    int cnt = 0;
    long long tn;
    tn = n+1;
    while(tn%2 == 0 && tn)
        tn /= 2, cnt++;
    tn = n-1;
    while(tn%2 == 0 && tn)
        tn /= 2, cnt--;
    return cnt > 0 ? (n+1) : (n-1);
}
long long sol(long long n) {
    if(n <= 1)  return n;
    if(n%2)
        return sol(check(n))+1;
    else
        return sol(n/2)+1;
}
int main() {
    long long n;
    while(scanf("%lld", &n) == 1)
        printf("%lld\n", sol(n));
    return 0;
}
