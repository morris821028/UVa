#include <stdio.h>

int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while(testcase--) {
        int sh, sm, eh, em;
        scanf("%d:%d %d:%d", &sh, &sm, &eh, &em);
        sh = sh*60 + sm, eh = eh*60 + em;
        int ah, am, bh, bm;
        scanf("%d:%d %d:%d", &ah, &am, &bh, &bm);
        ah = ah*60 + am, bh = bh*60 + bm;
        printf("Case %d: ", ++cases);
        if(eh < ah || sh > bh)
            puts("Hits Meeting");
        else
            puts("Mrs Meeting");
    }
    return 0;
}
