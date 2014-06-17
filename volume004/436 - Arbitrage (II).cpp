#include <stdio.h>
#include <string.h>
char dollar[31][50], a[50], b[50];
int encode(char s[]) {
    int i;
    for(i = 0; ; i++) {
        if(!strcmp(dollar[i], s))
            return i;
    }
}
int main() {
    int n, m, test = 0;
    int i, j, k;
    while(scanf("%d", &n) == 1 && n) {
        double map[31][31] = {}, f;

        for(i = 0; i < n; i++)
            scanf("%s", dollar[i]), map[i][i] = 1;
        scanf("%d", &m);

        while(m--) {
            scanf("%s %lf %s", a, &f, b);
            i = encode(a);
            j = encode(b);
            map[i][j] = f;
        }
        for(k = 0; k < n; k++) {
            for(i = 0; i < n; i++) {
                for(j = 0; j < n; j++) {
                    if(map[i][j] < map[i][k]*map[k][j])
                        map[i][j] = map[i][k]*map[k][j];
                }
            }
        }
        int flag = 0;
        for(i = 0; i < n; i++)
            if(map[i][i] > 1 + 1e-5)
                flag = 1;
        printf("Case %d: %s\n", ++test, flag ? "Yes" : "No");
    }
    return 0;
}
