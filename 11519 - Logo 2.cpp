#include <stdio.h>
#include <math.h>

int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        double px = 0, py = 0;
        double qx = 0, qy = 0;
        double theta = 0;
        double pi = acos(-1);
        char cmd[1000][10], arg[1000][10];
        int qqcmd = -1, qflag = 0, argv;
        int i, j;
        for(i = 0; i < n; i++) {
            scanf("%s %s", cmd[i], arg[i]);
            if(arg[i][0] == '?') {
                if(cmd[i][0] == 'l')       qqcmd = 0;
                else if(cmd[i][0] == 'r')  qqcmd = 1;
                else if(cmd[i][0] == 'f')  qqcmd = 2;
                else                       qqcmd = 3;
                qflag = 1;
                theta = 0;
                continue;
            }
            sscanf(arg[i], "%d", &argv);
            if(cmd[i][0] == 'l') {//left rotate
                theta = theta+argv;
                if(theta >= 360)    theta -= 360;
            } else if(cmd[i][0] == 'r') {//right rotate
                theta = theta-argv;
                if(theta < 0)       theta += 360;
            } else if(cmd[i][0] == 'f') {//forward move
                if(!qflag) {
                    px += argv*cos(theta*pi/180);
                    py += argv*sin(theta*pi/180);
                } else {
                    qx += argv*cos(theta*pi/180);
                    qy += argv*sin(theta*pi/180);
                }
            } else {//back move
                if(!qflag) {
                    px -= argv*cos(theta*pi/180);
                    py -= argv*sin(theta*pi/180);
                } else {
                    qx -= argv*cos(theta*pi/180);
                    qy -= argv*sin(theta*pi/180);
                }
            }
        }
        //printf("%lf %lf %lf %lf\n", px, py, qx, qy);
        if(qqcmd < 2) {
            for(j = 0; j < 360; j++) {
                px = 0, py = 0;
                theta = 0;
                for(i = 0; i < n; i++) {
                    if(arg[i][0] == '?') {
                        argv = j;
                    } else  sscanf(arg[i], "%d", &argv);
                    if(cmd[i][0] == 'l') {//left rotate
                        theta = theta+argv;
                        if(theta >= 360)    theta -= 360;
                    } else if(cmd[i][0] == 'r') {//right rotate
                        theta = theta-argv;
                        if(theta < 0)       theta += 360;
                    } else if(cmd[i][0] == 'f') {//forward move
                        px += argv*cos(theta*pi/180);
                        py += argv*sin(theta*pi/180);
                    } else {//back move
                        px -= argv*cos(theta*pi/180);
                        py -= argv*sin(theta*pi/180);
                    }
                }
                if(fabs(px) < 1e-2 && fabs(py) < 1e-2) {
                    printf("%d\n", j);
                    break;
                }
            }
        } else {
            if(qqcmd == 3)
                printf("%.0lf\n", sqrt(pow(px-qx, 2)+pow(py-qy, 2))+1e-8);
            else
                printf("%.0lf\n", sqrt(pow(px+qx, 2)+pow(py+qy, 2))+1e-8);

        }
    }
    return 0;
}
