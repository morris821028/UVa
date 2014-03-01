#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int x, y, p, q;
} rec;
rec R[500];
int cmp1(const void *i, const void *j) {
    rec *a, *b;
    a = (rec *)i, b = (rec *)j;
    return a->y - b->y;
}
int cmp2(const void *i, const void *j) {
    rec *a, *b;
    a = (rec *)i, b = (rec *)j;
    return a->x - b->x;
}
int in(int x, int y, int z, int w) {
    return (x <= z && z < y) || (x < w && w <= y) || (w >= y && z <= x);
}
int n;
int Step1() {
    int flag = 0, down = 0, i, j;
    do {
        down = 0;
        for(i = 0; i < n; i++) {
            int mmy = 0, tmp = R[i].q - R[i].y;
            for(j = 0; j <= i; j++) {
                if(in(R[i].x, R[i].p, R[j].x, R[j].p)) {
                    if(R[j].q <= R[i].y) {
                        mmy = mmy > R[j].q ? mmy : R[j].q;
                    }
                }
            }
            if(mmy != R[i].y)   down = 1;
            R[i].y = mmy, R[i].q = mmy+tmp;
        }
        flag += down;
    } while(down);
    return flag > 0;
}
int Step2() {
    int flag = 0, left = 0, i, j;
    do {
        left = 0;
        for(i = 0; i < n; i++) {
            int mmx = 0, tmp = R[i].p - R[i].x;
            for(j = 0; j <= i; j++) {
                if(in(R[i].y, R[i].q, R[j].y, R[j].q)) {
                    if(R[j].p <= R[i].x) {
                        mmx = mmx > R[j].p ? mmx : R[j].p;
                    }
                }
            }
            if(mmx != R[i].x)   left = 1;
            R[i].x = mmx, R[i].p = mmx+tmp;
        }
        flag += left;
    } while(left);
    return flag > 0;
}
int main() {
    int t, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d %d %d %d", &R[i].x, &R[i].y, &R[i].p, &R[i].q);
        int stop;
        do {
            stop = 0;
            qsort(R, n, sizeof(rec), cmp1);
            stop |= Step1();
            qsort(R, n, sizeof(rec), cmp2);
            stop |= Step2();
        } while(stop);
        int h = 0, w = 0;
        for(i = 0; i < n; i++) {
            h = h > R[i].p ? h : R[i].p;
            w = w > R[i].q ? w : R[i].q;
        }
        printf("%d %d\n", h, w);
    }
    return 0;
}
