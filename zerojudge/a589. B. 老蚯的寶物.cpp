#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int main() {
    int t, n;
    char cmd[2048][20], arg[2048][3];
    int arg2[2048], i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 1; i <= n; i++) {
            scanf("%s", &cmd[i]);
            if(cmd[i][0] == 'u')
                scanf("%d", &arg2[i]);
            else
                scanf("%s", &arg[i]);
        }
        string buf[32767];
        buf[0] = "";
        for(i = 1; i <= n; i++) {
            if(!strcmp("undo", cmd[i]))
                buf[i] = buf[i-arg2[i]-1];
            else if(!strcmp("pushfront", cmd[i]))
                buf[i] = arg[i][0] + buf[i-1];
            else
                buf[i] = buf[i-1] + arg[i][0];
            puts(buf[i].c_str());
        }
    }
    return 0;
}
