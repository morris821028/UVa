#include<stdio.h>
#include<string.h>
int check(char *s) {
    int i, l = strlen(s), accept = 0;
    for(i = l-1; i >= 0; i--) {
        switch(s[i]) {
            case 'p' ... 'z':accept ++;break;
            case 'N':if(accept == 0)
                        return 0;
                break;
            case 'C':if(accept < 2)
                        return 0;
                accept--;
                break;
            case 'D':if(accept < 2)
                        return 0;
                accept--;
                break;
            case 'E':if(accept < 2)
                        return 0;
                accept--;
                break;
            case 'I':if(accept < 2)
                        return 0;
                accept--;
                break;
            default:return 0;
        }
    }
    return (accept == 1);
}
main() {
    char s[1000];
    while(gets(s)) {
        puts(check(s) ? "YES" : "NO");
    }
    return 0;
} 
