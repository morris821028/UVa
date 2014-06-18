#include <stdio.h>

int main() {
    int i, j;
    int M[2005] = {}, J[2005] = {};
    for(i = 1; ; i++) {
        for(j = (i-1)*30; j < i*30 && j <= 2000; j++)
            M[j] = i*10;
        if(j != i*30)   break;
    }
    for(i = 1; ; i++) {
        for(j = (i-1)*60; j < i*60 && j <= 2000; j++)
            J[j] = i*15;
        if(j != i*60)   break;
    }
    scanf("%*d");
    int cases = 0, n;
    while(scanf("%d", &n) == 1) {
        int mm = 0, jj = 0;
        while(n--)
            scanf("%d", &i), mm += M[i], jj += J[i];
        printf("Case %d: ", ++cases);
        if(mm < jj)
            printf("Mile %d\n", mm);
        else if(mm > jj)
            printf("Juice %d\n", jj);
        else
            printf("Mile Juice %d\n", mm);
    }
    return 0;
}
