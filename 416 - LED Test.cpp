#include <stdio.h>
char g[10][8] = {
"YYYYYYN",//0
"NYYNNNN",//1
"YYNYYNY",//2
"YYYYNNY",//3
"NYYNNYY",//4
"YNYYNYY",//5
"YNYYYYY",//6
"YYYNNNN",//7
"YYYYYYY",//8
"YYYYNYY",//9
};
int main() {
    int n, i, j, k;
    char a[20][8];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%s", &a[i]);
        int flag = 0;
        for(i = 9; i >= n-1; i--) {
            int bad[10] = {};
            for(j = 0; j < n; j++) {
                for(k = 0; k < 7; k++) {
                    if(bad[k] && a[j][k] == 'Y')
                        break;
                    if(a[j][k] == 'N' && g[i-j][k] == 'Y')
                        bad[k] = 1;
                    else if(a[j][k] == 'Y' && g[i-j][k] == 'N')
                        break;
                }
                if(k != 7)  break;
            }
            if(j == n) {
                flag = 1;
                break;
            }
        }
        if(!flag)
            printf("MIS");
        puts("MATCH");
    }
    return 0;
}
