#include <stdio.h>
char s[2000005];
int main() {
    int L;
    while(scanf("%d", &L) == 1 && L) {
        while(getchar() != '\n');
        gets(s);
        int a = -1, b = -1, res = 0xfffffff;
        int i;
        for(i = 0; s[i]; i++) {
            if(s[i] == 'Z') {
                res = 0;
                break;
            }
            if(s[i] == 'R') a = i;
            if(s[i] == 'D') b = i;
            if(a != -1 && b != -1) {
                if(a-b > 0 && res > a-b)
                    res = a-b;
                if(b-a > 0 && res > b-a)
                    res = b-a;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
