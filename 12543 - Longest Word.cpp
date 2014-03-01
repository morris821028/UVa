#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

int main() {
    string end = "E-N-D", ans;
    int anslen = 0, i;
    char s[10005];
    while(scanf("%s", s) == 1) {
        if(!strcmp(s, "E-N-D"))
            break;
        for(i = 0; s[i]; i++) {
            if((s[i] >= 'a' && s[i] <= 'z') ||
                (s[i] >= 'A' && s[i] <= 'Z')) {
                char buf[105];
                int idx = 0;
                while((s[i] >= 'a' && s[i] <= 'z') ||
                (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '-') {
                    buf[idx++] = s[i++];
                }
                buf[idx] = '\0';
                if(idx > anslen)
                    anslen = idx, ans = buf;
            }
        }
    }
    if(anslen < 5)  ans = end;
    for(i = 0; i < anslen; i++) {
        if(ans[i] >= 'A' && ans[i] <= 'Z')
            putchar(ans[i]-'A'+'a');
        else
            putchar(ans[i]);
    }
    puts("");
    return 0;
}
