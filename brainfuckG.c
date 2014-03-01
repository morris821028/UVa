#include <stdio.h>
int main() {
    char s[128];
    int i, j;
    while(gets(s)) {
        int pos = 0;
        int ptr[8];
        for(i = 0; i < 7; i++) {
            int last = i;
            for(j = 0; s[j]; j++) {
                if(s[j]&(1<<i)) {
                    while(last < j+7)
                        printf(">"), last++, pos++;
                    printf("+");
                }
            }
            ptr[i] = last;
            while(last > i+1)
                printf("<"), pos--, last--;
            if(i != 6)
                printf("++[");
        }
        for(i = 5; i >= 0; i--)
            printf("<-]");
        for(i = 0; i < 6; i++)
            printf(">");
        for(i = 0; s[i]; i++)
            printf(".>");
        puts("");
    }
    return 0;
}
