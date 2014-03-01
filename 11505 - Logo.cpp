#include <stdio.h>
#include <math.h>

int main() {
    int t, n;
    char cmd[5];
    const double pi = acos(-1);
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        double theta = 0, arg;
        double x = 0, y = 0;
        while(n--) {
            scanf("%s %lf", cmd, &arg);
            if(cmd[0] == 'f')
                x += arg*cos(theta*pi/180), y += arg*sin(theta*pi/180);
            else if(cmd[0] == 'b')
                x -= arg*cos(theta*pi/180), y -= arg*sin(theta*pi/180);
            else if(cmd[0] == 'l') {
                theta += arg;
                if(theta >= 360)
                    theta -= 360;
            } else {
                theta -= arg;
                if(theta < 0)
                    theta += 360;
            }
        }
        printf("%.lf\n", sqrt(x*x+y*y));
    }
    return 0;
}
