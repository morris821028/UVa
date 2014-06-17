#include <stdio.h>
#include <math.h>
char f[1000001];
int apart(int n) {
    int i, sq = (int)sqrt(n);
    int flag = 0;
    for(i = 2; i <= sq; i++) {
        if(n%i == 0) {
            while(n%i == 0)
                n /= i;
            flag = 1;
            break;
        }
    }
    if(flag && n == 1)
        return i;
    if(!flag)
        return n;
    return 0;
}
int bigNum[101] = {2}, tmp[101] = {};
int len = 1;
void mult(int n) {
    int i, j;
    for(i = 0; i <= len; i++)
        tmp[i] = bigNum[i]*n;
    for(i = len+1; i <= len+10; i++)
        tmp[i] = 0;
    for(i = 0; i <= len+10; i++) {
        tmp[i+1] += tmp[i]/10, tmp[i] %= 10;
    }
    j = 0;
    while(tmp[j] == 0)  j++;
    for(i = 0; i <= len+10; i++, j++)
        bigNum[i] = tmp[j];
    len += 10;
    while(!bigNum[len]) len--;
    if(len > 10)    len = 10;
}
int main() {
    f[1] = 1, f[2] = 2;
    int i, j;
    for(i = 3; i <= 1000000; i++) {
        j = apart(i);
        if(j)   mult(j);
        f[i] = bigNum[0];
    }
    while(scanf("%d", &i) == 1 && i)
        printf("%d\n", f[i]);
    return 0;
}
