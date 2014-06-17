#include <stdio.h>
#include <string.h>
int main() {
    char dir[10005][30], word[30];
    int t, len[10005], i, j;
    scanf("%d", &t);
    while(t--) {
        int n = 0;
        while(scanf("%s", dir[n]) == 1 && dir[n][0] != '#')
            len[n] = strlen(dir[n]), n++;
        while(scanf("%s", word) == 1 && word[0] != '#') {
            int flag = 0, wlen = strlen(word);
            for(i = 0; i < n; i++) {
                if(!strcmp(word, dir[i])) {
                    printf("%s is correct\n", word);
                    flag = 1;
                    break;
                }
            }
            if(flag)    continue;
            printf("%s:", word);
            for(i = 0; i < n; i++) {
                //delete
                int flag2 = 0, idx1, idx2;
                if(wlen == len[i]-1)
                for(j = 0; j < len[i]; j++) {
                    idx1 = 0, idx2 = 0;
                    while(word[idx1] && dir[i][idx2]) {
                        if(idx2 == j)   idx2++;
                        if(word[idx1] != dir[i][idx2])  break;
                        idx1++, idx2++;
                    }
                    if(idx2 == j)   idx2++;
                    if(!word[idx1] && !dir[i][idx2]) {
                        printf(" %s", dir[i]);
                        flag2 = 1;
                        break;
                    }
                }
                if(flag2)   continue;
                //replace
                if(wlen == len[i])
                for(j = 0; j < len[i]; j++) {
                    idx1 = 0, idx2 = 0;
                    while(word[idx1] && dir[i][idx2]) {
                        if(word[idx1] != dir[i][idx2] && idx1 != j)  break;
                        idx1++, idx2++;
                    }
                    if(!word[idx1] && !dir[i][idx2]) {
                        printf(" %s", dir[i]);
                        flag2 = 1;
                        break;
                    }
                }
                if(flag2)   continue;
                //insert
                if(wlen == len[i]+1)
                for(j = 0; j < wlen; j++) {
                    idx1 = 0, idx2 = 0;
                    while(word[idx1] && dir[i][idx2]) {
                        if(idx1 == j)   idx1++;
                        if(word[idx1] != dir[i][idx2])  break;
                        idx1++, idx2++;
                    }
                    if(idx1 == j)   idx1++;
                    if(!word[idx1] && !dir[i][idx2]) {
                        printf(" %s", dir[i]);
                        flag2 = 1;
                        break;
                    }
                }
            }
            puts("");
        }
        if(t)
            puts("");
    }
    return 0;
}
