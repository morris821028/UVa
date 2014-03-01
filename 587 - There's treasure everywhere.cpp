#include <stdio.h>
#include <math.h>
#include <string.h>
int main() {
    char str[205];
    int t = 0;
    while(gets(str)) {
        if(!strcmp(str, "END"))
            break;
        printf("Map #%d\n", ++t);
        double x = 0, y = 0, sqr2 = sqrt(2);
        int tmp = 0, i;
        for(i = 0; str[i]; i++) {
            if(str[i] >= '0' && str[i] <= '9')
                tmp = tmp*10 + str[i]-'0';
            else {
                if(str[i] == ',' || str[i] == '.')
                    continue;
                if(str[i] == 'N') {
                    if(str[i+1] == ',' || str[i+1] == '.') {
                        y += tmp;
                        i++;
                    } else if(str[i+1] == 'W') {
                        x -= tmp*sqr2/2;
                        y += tmp*sqr2/2;
                        i += 2;
                    } else {
                        x += tmp*sqr2/2;
                        y += tmp*sqr2/2;
                        i += 2;
                    }
                } else if(str[i] == 'W') {
                    x -= tmp;
                    i++;
                } else if(str[i] == 'E') {
                    x += tmp;
                    i++;
                } else {
                    if(str[i+1] == ',' || str[i+1] == '.') {
                        y -= tmp;
                        i++;
                    } else if(str[i+1] == 'W') {
                        x -= tmp*sqr2/2;
                        y -= tmp*sqr2/2;
                        i += 2;
                    } else {
                        x += tmp*sqr2/2;
                        y -= tmp*sqr2/2;
                        i += 2;
                    }
                }
                tmp = 0;
            }
        }
        printf("The treasure is located at (%.3lf,%.3lf).\n", x, y);
        printf("The distance to the treasure is %.3lf.\n\n", sqrt(x*x+y*y));
    }
    return 0;
}
