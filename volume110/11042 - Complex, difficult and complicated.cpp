#include <stdio.h>

int main() {
    scanf("%*d");
    int a, b;
    while(scanf("%d %d", &a, &b) == 2) {
        if(!b) {
            puts("1");
        } else if(2*a*b == 0) {
            puts("2");
        } else {
            double la = a, lb = b;
            if(la*lb*(la*la-lb*lb) == 0) {
                double c = a*a-b*b, ab = 2*a*b;
                if((c*c-ab*ab) <= (1<<30))
                    puts("4");
                else
                    puts("TOO COMPLICATED");
            } else
                puts("TOO COMPLICATED");
        }
    }
    return 0;
}
