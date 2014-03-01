#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>
using namespace std;
int w[30], n, C;
int test() {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            if((C/w[i])%n == (C/w[j])%n) {
                C = min((C/w[i]+1)*w[i], (C/w[j]+1)*w[j]);
                return 0;
            }
        }
    }
    return 1;
}
int main() {
    char s[100];
    while(gets(s)) {
        int len = strlen(s);
        int i, j;
        n = 0;
        for(i = 0; i < len; i++) {
            if(isalpha(s[i])) {
                char tmp[100];
                sscanf(s+i, "%s", tmp);
                int sublen = strlen(tmp);
                w[n] = 0;
                for(j = 0; j < sublen; j++)
                    w[n] = (w[n]<<5) + (tmp[j]-'a'+1);
                i += sublen;
                n++;
            }
        }
        C = 2147483647;
        for(i = 0; i < n; i++) {
            C = min(C, w[i]);
        }
        while(!test());
        printf("%s\n%d\n\n", s, C);
    }
    return 0;
}
