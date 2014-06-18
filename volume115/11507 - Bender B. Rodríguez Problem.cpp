#include <stdio.h>
#include <string.h>
int main() {
    int n;
    char cmd[100000][3];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < n; i++)
            scanf("%s", cmd[i]);
        int dir = 0;
        //+x(0), -x(1), +y(2), -y(3), +z(4), -z(5)
        for(i = 0; i < n; i++) {
            if(!strcmp(cmd[i], "No"))
                continue;
            if(!strcmp(cmd[i], "+z")) {
                if(dir == 0)        dir = 4;//+x->+z
                else if(dir == 1)   dir = 5;//-x->-z
                else if(dir == 4)   dir = 1;//+z->-x
                else if(dir == 5)   dir = 0;//-z->+x
            }
            if(!strcmp(cmd[i], "-z")) {
                if(dir == 0)        dir = 5;//+x->-z
                else if(dir == 1)   dir = 4;//-x->+z
                else if(dir == 4)   dir = 0;//+z->+x
                else if(dir == 5)   dir = 1;//-z->-x
            }
            if(!strcmp(cmd[i], "+y")) {
                if(dir == 0)        dir = 2;//+x->+y
                else if(dir == 1)   dir = 3;//-x->-y
                else if(dir == 2)   dir = 1;//+y->-x
                else if(dir == 3)   dir = 0;//-y->+x
            }
            if(!strcmp(cmd[i], "-y")) {
                if(dir == 0)        dir = 3;//+x->-y
                else if(dir == 1)   dir = 2;//-x->+y
                else if(dir == 2)   dir = 0;//+y->+x
                else if(dir == 3)   dir = 1;//-y->-x
            }
        }
        if(dir == 0)    puts("+x");
        if(dir == 1)    puts("-x");
        if(dir == 2)    puts("+y");
        if(dir == 3)    puts("-y");
        if(dir == 4)    puts("+z");
        if(dir == 5)    puts("-z");
    }
    return 0;
}
