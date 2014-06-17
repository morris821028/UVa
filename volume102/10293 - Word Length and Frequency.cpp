#include <stdio.h>
#include <string.h>
int main() {
    char c;
    do {
        int i, j, len = 0, hyp = 0, f = 0;
        int cnt[100] = {};
        while(c = getchar()) {
            if(c == EOF)    return 0;
            if(c == '-')    hyp = 1;
            else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                f = 1;
                len++;
                hyp = 0;
            } else {
                if(hyp == 1 && c == '\n')
                    continue;
                if(f && c == '\'')
                    continue;
                if(f) {
                    f = 0;
                    cnt[len]++;
                    hyp = 0;
                    len = 0;
                }
            }
            if(c == '#')    break;
        }
        for(i = 1; i < 100; i++)
            if(cnt[i])
                printf("%d %d\n", i, cnt[i]);
        puts("");
    } while(1);
    return 0;
}
