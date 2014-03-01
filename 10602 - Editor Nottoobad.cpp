#include <stdio.h>
#include <string.h>

int main() {
    int t, n;
    char word[105][105];
    int wlen[105], i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%s", &word[i]);
            wlen[i] = strlen(word[i]);
        }
        int st = 0;
        int used[105] = {}, res = wlen[0];
        int way[105];
        used[st] = 1;
        for(i = 0; i < n; i++) {
            way[i] = st;
            if(i == n-1)    break;
            int mx = -1, next = 0;
            for(j = 0; j < n; j++) {
                if(used[j])
                    continue;
                for(k = 0; word[st][k] == word[j][k] && word[st][k]; k++);
                if(k > mx)
                    mx = k, next = j;
            }
            if(wlen[next]-mx < wlen[next])
                res += wlen[next]-mx;
            else
                res += wlen[next];
            st = next;
            used[st] = 1;
        }
        printf("%d\n", res);
        for(i = 0; i < n; i++)
            puts(word[way[i]]);
    }
    return 0;
}
/*
3
3
this
thin
thing
4
popcorn
apple
apricote
plum
2
hello
hello
*/
