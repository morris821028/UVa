#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int w[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int calcLED(int n) {
    char buf[32];
    sprintf(buf, "%d", n);
    int ret = 0;
    for (int i = 0; buf[i]; i++)
        ret += w[buf[i] - '0'];
    return ret;
}
int main() {
    int cases = 0;
    int hh, mm, ss, x;
    char cmd[32];
    while (scanf("%*s") == 0) {
        scanf("%d:%d:%d", &hh, &mm, &ss);
        int pre = hh * 3600 + mm * 60 + ss, now;
        int home = 0, guest = 0, ret = 0;
        while (scanf("%s", cmd) == 1) {
            scanf("%d:%d:%d", &hh, &mm, &ss);
            now = hh * 3600 + mm * 60 + ss;
            ret += (now - pre) * (calcLED(home) + calcLED(guest));
            if (cmd[0] == 'E')  break;
            scanf("%s %d", cmd, &x);
            if (cmd[0] == 'h')  home += x;
            else                guest += x;
            pre = now;
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}
/*
 START 09:00:00
 SCORE 09:01:05 home 2
 SCORE 09:10:07 guest 3
 END 09:15:00
 START 09:00:00
 SCORE 10:00:00 home 1
 SCORE 11:00:00 home 1
 SCORE 12:00:00 home 1
 SCORE 13:00:00 home 1
 SCORE 14:00:00 home 1
 SCORE 15:00:00 home 1
 SCORE 16:00:00 home 1
 SCORE 17:00:00 home 1
 SCORE 18:00:00 home 1
 SCORE 19:00:00 home 1
 SCORE 20:00:00 home 1
 END 21:00:00
*/