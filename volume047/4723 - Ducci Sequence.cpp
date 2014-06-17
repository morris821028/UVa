#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
using namespace std;
int a[15], stkIdx;
char str[100];
void tran(int n, int st) {
    if(!n && st)
        str[stkIdx++] = '0';
    if(!n)  return;
    tran(n/10, 0);
    str[stkIdx++] = n%10 + '0';
}
void int2str(int n) {
    stkIdx = 0;
    static int i;
    for(i = 0; i < n; i++) {
        tran(a[i], 1);
        str[stkIdx++] = ' ';
    }
    str[stkIdx-1] = '\0';
}
int main() {
    int t, n, i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int sum = 0;
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]), sum += a[i];
        map<string, bool> r;
        while(sum) {
            int2str(n);
            if(r[str])    break;
            r[str] = true;
            sum = 0;
            for(i = 1, j = a[0]; i < n; i++)
                a[i-1] = abs(a[i-1] - a[i]), sum += a[i-1];
            a[n-1] = abs(a[n-1]-j);
            sum += a[n-1];
        }
        if(sum)
            puts("LOOP");
        else
            puts("ZERO");
    }
    return 0;
}
