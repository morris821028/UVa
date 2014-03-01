#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int count(int n) {
    char s[12];
    sprintf(s, "%d", n);
    int i, sum = 0;
    for(i = 0; s[i]; i++)
        sum += s[i]-'0';
    return sum;
}
int C(int n) {
    int i, ans;
    int digits1 = count(n), digits2 = 0, flag = 1;
    ans = n;
    for(i = 2; i <= (int)sqrt(n); i++) {
        if(n%i == 0) {
            int time = 0;
            while(n%i == 0) {
                time++;
                n /= i;
            }
            digits2 += time*count(i);
            flag = 0;
        }
    }
    if(n != 1)
        digits2 += count(n);
    if(digits1 == digits2 && flag == 0) {
        printf("%d\n", ans);
        return 1;
    }
    return 0;
}
int main() {
    int i;
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(i = n+1; ; i++)
            if(C(i) == 1)
                break;
    }
    return 0;
}
