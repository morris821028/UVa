#include <stdio.h>
#include <string.h>
#define maxN 20005
char line[maxN], *token[maxN];
int main() {
    while(gets(line)) {
        int n = 0, i, j, k;
        for(i = 0; line[i]; i++) {
            if(line[i] > 32) {
                token[n++] = line+i;
                while(line[i] > 32)
                    i++;
                if(line[i] == '\0')
                    break;
                line[i] = '\0';
            }
        }
        while(1) {
            int flag = 0;
            for(i = 0; i < n; i++) {
                for(j = i+1; j < n; j++) {
                    int len = j-i; // [i...j-1],[j...j+len-1]
                    if(j+len-1 >= n)    break;
                    for(k = 0; k < len; k++)
                        if(strcmp(token[i+k], token[j+k]))
                            break;
                    if(k == len) {
                        for(k = j+len, j = i+len; k < n; k++, j++)
                            token[j] = token[k];
                        flag = 1, i = j = n;
                        n -= len;
                    }
                }
            }
            if(!flag)   break;
        }
        for(i = 0; i < n; i++) {
            if(i)   putchar(' ');
            printf("%s", token[i]);
        }
        puts("");
    }
    return 0;
}
