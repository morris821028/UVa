#include <stdio.h>
#include <string.h>

int main() {
    int t, n, i;
    int cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        char sub[101][50], in[50];
        int D[101], d;
        for(i = 0; i < n; i++)
            scanf("%s %d", &sub[i], &D[i]);
        scanf("%d %s", &d, in);
        printf("Case %d: ", ++cases);
        for(i = 0; i < n; i++) {
            if(!strcmp(sub[i], in)) {
                if(d >= D[i])
                    puts("Yesss");
                else if(d+5 >= D[i])
                    puts("Late");
                else
                    puts("Do your own homework!");
                break;
            }
        }
        if(i == n)
            puts("Do your own homework!");
    }
    return 0;
}
