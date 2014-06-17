#include <stdio.h>
#define LL long long
int dfs(LL a, LL b) { //a < b
    if(!a)
        return 0;
    int win = 0;
    win |= !dfs(b%a, a);
    if(b/a != 1 && win == 0)
        win |= !dfs(b, b+b%a);
    return win;
}
int main() {
    LL a, b, c;
    while(scanf("%lld %lld", &a, &b) == 2) {
        if(a == 0 && b == 0)
            break;
        if(a > b)
            c = a, a = b, b = c;
        printf("%s wins\n", dfs(a, b) ? "Stan" : "Ollie");
    }
    return 0;
}
