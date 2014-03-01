#include <stdio.h>
#include <math.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
typedef struct {
    int x, y;
} Point;
long long cross(Point &o, Point &a, Point &b) {
    return (a.x - o.x)*(b.y - o.y) - (a.y - o.y)*(b.x - o.x);
}
int inShape(Point &a, Point &b, Point &c, Point &t) {
    if(cross(a, b, t)*cross(a, c, t) > 0) {
        return 0;
    }
    if(cross(b, a, t)*cross(b, c, t) > 0) {
        return 0;
    }
    if(cross(c, a, t)*cross(c, b, t) > 0) {
        return 0;
    }
    return 1;
}
int parseDouble(char *str) {/*100X*/
    int tmp = 0, i, cnt = 0;
    for(i = 0; str[i]; i++) {
        if(str[i] >= '0' && str[i] <= '9')
            tmp = tmp*10 + str[i]-'0';
        else {
            i++;
            for(; str[i]; i++) {
                tmp = tmp*10 + str[i]-'0';
                cnt++;
                if(cnt == 2)
                    return tmp;
            }
            while(cnt < 2)
                tmp = tmp*10, cnt++;
            return tmp;
        }
    }
    while(cnt < 2)
        tmp = tmp*10, cnt++;
    return tmp;
}
int main() {
    Point P[3];
    int x, y;
    char str1[10], str2[10];
    while(true) {
        int lx = 100001, rx = -1, ly = 100001, ry = -1;
        int i, j, cnt = 0;
        Point t;
        for(i = 0; i < 3; i++) {
            scanf("%s %s", str1, str2);
            x = parseDouble(str1);
            y = parseDouble(str2);
            lx = min(lx, x);
            rx = max(rx, x);
            ly = min(ly, y);
            ry = max(ry, y);
            P[i].x = x, P[i].y = y;
        }
        if(!P[0].x && !P[0].y && !P[1].x && !P[1].y && !P[2].x && !P[2].y)
            break;

        if(lx%100 != 0) lx += 100;
        if(ly%100 != 0) ly += 100;
        lx = lx/100*100, rx = rx/100*100;
        ly = ly/100*100, ry = ry/100*100;
        if(lx < 100)  lx = 100;
        if(ly < 100)  ly = 100;
        if(rx > 9900)  rx = 9900;
        if(ry > 9900)  ry = 9900;
        for(i = lx; i <= rx; i += 100)
            for(j = ly; j <= ry; j += 100) {
                t.x = i, t.y = j;
                if(inShape(P[0], P[1], P[2], t)) {
                    cnt++;
                }
            }
        printf("%4d\n", cnt);
    }
    return 0;
}
