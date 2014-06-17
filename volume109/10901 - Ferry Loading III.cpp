#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
struct car {
    int t, in;
    car(int x, int y) {
        t = x;
        in = y;
    }
};
int main() {
    int testcase, n, m, t, i;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d %d", &n, &t, &m);
        int time;
        char s[50];
        queue<car> LEFT, RIGHT;
        for(i = 0; i < m; i++) {
            scanf("%d %s", &time, s);
            if(s[0] == 'l')
                LEFT.push(car(time, i));
            else
                RIGHT.push(car(time, i));
        }
        int now_time = 0, flag = 0;
        int res[10000];
        while(1) {
            if(LEFT.empty() && RIGHT.empty())
                break;
            //printf("time %d : %s\n", now_time, flag ? "right" : "left");
            int tn = 0;
            if(flag == 0) { // LEFT bank
                while(tn < n && !LEFT.empty() && LEFT.front().t <= now_time)
                    tn++, res[LEFT.front().in] = now_time+t, LEFT.pop();
                if(tn) { // goto either
                    now_time += t;
                    flag = 1-flag;
                    continue;
                }
                if(RIGHT.empty() || (!LEFT.empty() && LEFT.front().t <= RIGHT.front().t)) {
                    now_time = LEFT.front().t;// waiting left
                    while(tn < n && !LEFT.empty() && LEFT.front().t <= now_time)
                        tn++, res[LEFT.front().in] = now_time+t, LEFT.pop();
                    now_time += t;
                } else {
                    if(!RIGHT.empty() || LEFT.empty() && LEFT.front().t > RIGHT.front().t)
                        now_time = max(RIGHT.front().t, now_time)+t;//max tricky
                    else
                        now_time += t;
                }
            } else {
                while(tn < n && !RIGHT.empty() && RIGHT.front().t <= now_time)
                    tn++, res[RIGHT.front().in] = now_time+t, RIGHT.pop();
                if(tn) {
                    now_time += t;
                    flag = 1-flag;
                    continue;
                }
                if(LEFT.empty() || (!RIGHT.empty() && LEFT.front().t >= RIGHT.front().t)) {
                    now_time = RIGHT.front().t;
                    while(tn < n && !RIGHT.empty() && RIGHT.front().t <= now_time)
                        tn++, res[RIGHT.front().in] = now_time+t, RIGHT.pop();
                    now_time += t;
                } else {
                    if(!LEFT.empty() || RIGHT.empty() && LEFT.front().t < RIGHT.front().t)
                        now_time = max(LEFT.front().t, now_time)+t;
                    else
                        now_time += t;
                }
            }
            flag = 1-flag;
        }
        for(i = 0; i < m; i++)
            printf("%d\n", res[i]);
        if(testcase)
            puts("");
    }
    return 0;
}
/*
1
1113 1072 11
8631 left
12526 left
15884 left
19388 left
24635 left
30627 right
30627 left
31757 left
35635 right
36133 left
40444 left
*/
