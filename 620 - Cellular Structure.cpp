#include <stdio.h>
#include <string.h>

int main() {
    char s[1005];
    int n;
    while(scanf("%d", &n) == 1) {
        while(n--) {
            scanf("%s", s);
            int len = strlen(s);
            if(!len%2) puts("NUTANT");
            else if(len == 1) {
                puts(s[0] == 'A' ? "SIMPLE" : "MUTANT");
            } else {
                if(s[0] == 'B' && s[len-1] == 'A')
                    puts("MUTAGENIC");
                else if(s[len-1] == 'B' && s[len-2] == 'A')
                    puts("FULLY-GROWN");
                else
                    puts("MUTANT");
            }
        }
    }
    return 0;
}
