#include <stdio.h>
#include <math.h>
int main() {
    int t, a, b;
    const double pi = acos(-1);
    char cmd[50];
    scanf("%d", &t);
    gets(cmd);
    while(t--) {
        gets(cmd);
        if(sscanf(cmd, "%d %d", &a, &b) == 2) {
            printf("%.4lf\n", 2*a*b*pi);
        } else {
            sscanf(cmd, "%d", &a);
            printf("%.4lf\n", a*a*pi/8);
        }
    }
    return 0;
}
