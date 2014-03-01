#include <stdio.h>

int main() {
    int t;
    char cha;
    scanf("%d", &t);
    while((cha = getchar()) != '\n');
    while(t--) {
        int p = 0, ans = 0;
        while((cha = getchar()) != '\n') {
            if(cha == 'p')
                p++;
            else if(cha == 'q') {
                if(p > 0)
                    ans++, p--;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
