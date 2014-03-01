#include <stdio.h>
#include <string.h>
int main() {
    char cipher[500], plain[500];
    int i, k;
    while(scanf("%d", &k) == 1 && k) {
        scanf("%s", cipher);
        int len = strlen(cipher);
        for(i = 0; i < len; i++) {
            int code;
            if(cipher[i] == '.')    code = 27;
            else if(cipher[i] == '_')   code = 0;
            else code = cipher[i] - 'a'+1;
            code = (code+i)%28;
            if(code == 0)   code = '_';
            else if(code == 27) code = '.';
            else code = code - 1 + 'a';
            plain[(k*i)%len] = code;
        }
        plain[len] = '\0';
        puts(plain);
    }
    return 0;
}
