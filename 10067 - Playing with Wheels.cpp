#include <stdio.h>
int main() {
    scanf("%*d");
    int a, b, c, d, st, ed;
    while(scanf("%d %d %d %d", &a, &b, &c, &d) == 4) {
        st = a*1000+b*100+c*10+d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        ed = a*1000+b*100+c*10+d;
        int ban[10005] = {}, tn, i, j, n, tmp;
        scanf("%d", &n);
        while(n--) {
            scanf("%d %d %d %d", &a, &b, &c, &d);
            tn = a*1000+b*100+c*10+d;
            ban[tn] = 1;
        }
        int Q[10005], qt, used[10005] = {}, step[10005]= {};
        Q[qt = 0] = st, used[st] = 1, step[st] = 1;
        for(i = 0; i <= qt; i++) {
            tn = Q[i];
            a = tn/1000, b = tn%1000/100, c = tn%100/10, d = tn%10;
            tmp = (a+1)%10*1000+b*100+c*10+d;
            if(used[tmp] == 0 && ban[tmp] == 0) {
                used[tmp] = 1;
                step[tmp] = step[tn]+1;
                Q[++qt] = tmp;
            }
            tmp = (a+9)%10*1000+b*100+c*10+d;
            if(used[tmp] == 0 && ban[tmp] == 0) {
                used[tmp] = 1;
                step[tmp] = step[tn]+1;
                Q[++qt] = tmp;
            }
            tmp = a*1000+(b+1)%10*100+c*10+d;
            if(used[tmp] == 0 && ban[tmp] == 0) {
                used[tmp] = 1;
                step[tmp] = step[tn]+1;
                Q[++qt] = tmp;
            }
            tmp = a*1000+(b+9)%10*100+c*10+d;
            if(used[tmp] == 0 && ban[tmp] == 0) {
                used[tmp] = 1;
                step[tmp] = step[tn]+1;
                Q[++qt] = tmp;
            }
            tmp = a*1000+b*100+(c+1)%10*10+d;
            if(used[tmp] == 0 && ban[tmp] == 0) {
                used[tmp] = 1;
                step[tmp] = step[tn]+1;
                Q[++qt] = tmp;
            }
            tmp = a*1000+b*100+(c+9)%10*10+d;
            if(used[tmp] == 0 && ban[tmp] == 0) {
                used[tmp] = 1;
                step[tmp] = step[tn]+1;
                Q[++qt] = tmp;
            }
            tmp = a*1000+b*100+c*10+(d+1)%10;
            if(used[tmp] == 0 && ban[tmp] == 0) {
                used[tmp] = 1;
                step[tmp] = step[tn]+1;
                Q[++qt] = tmp;
            }
            tmp = a*1000+b*100+c*10+(d+9)%10;
            if(used[tmp] == 0 && ban[tmp] == 0) {
                used[tmp] = 1;
                step[tmp] = step[tn]+1;
                Q[++qt] = tmp;
            }
            if(used[ed])    break;
        }
        if(used[ed])
            printf("%d\n", step[ed]-1);
        else
            puts("-1");

    }
    return 0;
}
