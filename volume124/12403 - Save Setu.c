#include <stdio.h>
#include <string.h>

int main() {
    int t, sum = 0, x;
    char str[20];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", str);
        if(!strcmp(str, "donate")) {
            scanf("%d", &x);
            sum += x;
        } else {
            printf("%d\n", sum);
        }
    }
    return 0;
}
