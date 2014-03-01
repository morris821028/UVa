#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int st, ed;
} Time;
int cmp(const void *i, const void *j) {
    Time *a, *b;
    a = (Time *)i, b = (Time *)j;
    return a->st - b->st;
}
int main() {
    int n, i, a, b, c, d, day = 0;
    Time D[100];
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++) {
            scanf("%d:%d %d:%d", &a, &b, &c, &d);
            D[i].st = a*60 + b;
            D[i].ed = c*60 + d;
            while(getchar() != '\n');
        }
        qsort(D, n, sizeof(Time), cmp);
        int lastT = 600, ans = 0, st;
        for(i = 0; i < n; i++) {
            if(abs(lastT - D[i].st) > ans)
                ans = abs(lastT - D[i].st), st = lastT;
            lastT = D[i].ed;
        }
        if(abs(18*60 - lastT) > ans)
            ans = abs(18*60 - lastT), st = lastT;
        printf("Day #%d: the longest nap starts at ", ++day);
        printf("%02d:%02d and will last for ", st/60, st%60);
        if(ans >= 60)
            printf("%d hours and ", ans/60);
        printf("%d minutes.\n", ans%60);
    }
    return 0;
}
