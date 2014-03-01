#include <stdio.h>
#include <set>
#include <string.h>
using namespace std;
int main() {
    char s[1024];
    int i;
    while(scanf("%s", s) == 1) {
        int l3flag = 0, l4flag = 0;
        char buf3[3], buf4[4];
        int len = strlen(s);
        for(i = 0; i < len; i++) {
            if(s[i] == s[i+2] && i+2 < len) { // len 3
                if(l3flag == 0) {
                    buf3[0] = s[i];
                    buf3[1] = s[i+1];
                    buf3[2] = s[i+2];
                    l3flag = 1;
                } else {
                    if(buf3[0] == s[i] && buf3[1] == s[i+1]
                       && buf3[2] == s[i+2]);
                    else
                        l3flag = 2;
                }
            }
            if(s[i] == s[i+3] && s[i+1] == s[i+2] && i+3 < len) { // len 4
                if(l4flag == 0) {
                    buf4[0] = s[i];
                    buf4[1] = s[i+1];
                    buf4[2] = s[i+2];
                    buf4[3] = s[i+3];
                    l4flag = 1;
                } else {
                    if(buf4[0] == s[i] && buf4[1] == s[i+1]
                       && buf4[2] == s[i+2] && buf4[3] == s[i+3]);
                    else
                        l4flag = 2;
                }
            }
        }
        if(l3flag == 2 || l4flag == 2)
            puts(s);
    }
    return 0;
}
