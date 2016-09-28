#include <stdio.h>
 
int main() {
    int p1x, p1y;
    int p2x, p2y;
    int p3x, p3y;
    scanf("%d %d", &p1x, &p1y);
    scanf("%d %d", &p2x, &p2y);
    scanf("%d %d", &p3x, &p3y);
    if ((p2x-p1x)*(p3y-p1y)-(p2y-p1y)*(p3x-p1x) < 0) {
        int tmp;
        tmp = p2x, p2x = p3x, p3x = tmp;
        tmp = p2y, p2y = p3y, p3y = tmp;
    }
    int lx = p1x, rx = p1x, ly = p1y, ry = p1y;
    lx = lx < p2x ? lx : p2x;
    lx = lx < p3x ? lx : p3x;
    rx = rx > p2x ? rx : p2x;
    rx = rx > p3x ? rx : p3x;
    ly = ly < p2y ? ly : p2y;
    ly = ly < p3y ? ly : p3y;
    ry = ry > p2y ? ry : p2y;
    ry = ry > p3y ? ry : p3y;
    int ret = 0;
    for (int i = lx; i <= rx; i++) {
        for (int j = ly; j <= ry; j++) {
            int in = 0, x, y;
            x = i, y = j;
            in += (x-p1x)*(p2y-p1y) - (y-p1y)*(p2x-p1x) <= 0 &&
                    (x-p2x)*(p3y-p2y) - (y-p2y)*(p3x-p2x) <= 0 &&
                     (x-p3x)*(p1y-p3y) - (y-p3y)*(p1x-p3x) <= 0;
            x = i+1, y = j;
            in += (x-p1x)*(p2y-p1y) - (y-p1y)*(p2x-p1x) <= 0 &&
                    (x-p2x)*(p3y-p2y) - (y-p2y)*(p3x-p2x) <= 0 &&
                     (x-p3x)*(p1y-p3y) - (y-p3y)*(p1x-p3x) <= 0;
            x = i, y = j+1;
            in += (x-p1x)*(p2y-p1y) - (y-p1y)*(p2x-p1x) <= 0 &&
                    (x-p2x)*(p3y-p2y) - (y-p2y)*(p3x-p2x) <= 0 &&
                     (x-p3x)*(p1y-p3y) - (y-p3y)*(p1x-p3x) <= 0;
            x = i+1, y = j+1;
            in += (x-p1x)*(p2y-p1y) - (y-p1y)*(p2x-p1x) <= 0 &&
                    (x-p2x)*(p3y-p2y) - (y-p2y)*(p3x-p2x) <= 0 &&
                     (x-p3x)*(p1y-p3y) - (y-p3y)*(p1x-p3x) <= 0;
            ret += in == 4;
        }
    }
    printf("%d\n", ret);
    return 0;
}
