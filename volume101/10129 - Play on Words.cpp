#include <stdio.h>
#include <string.h>
int used[26] = {}, map[26][26] = {};
void color(int nd) {
    if(used[nd])
        return;
    used[nd] = 1;
    int i;
    for(i = 0; i < 26; i++) {
        if(map[nd][i])
            color(i);
    }
}
int main() {
    int t, n;
    char str[1001];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        getchar();
        memset(map, 0, sizeof(map));
        int outdeg[26] = {}, indeg[26] = {};
        int i, j, len;
        while(n--) {
            scanf("%s", str);
            len = strlen(str);
            i = str[0]-'a', j = str[len-1]-'a';
            map[i][j]++;
            outdeg[i]++, indeg[j]++;
        }
        int st, sn = 0, ed, en = 0;
        int diff = 0;
        for(i = 0;  i < 26; i++) {
            //printf("%d %d %d\n", i, indeg[i], outdeg[i]);
            if(indeg[i]+1 == outdeg[i]) {
                st = i, sn++;
            } else if(indeg[i] == outdeg[i]+1) {
                ed = i, en++;
            } else {
                if(indeg[i] != outdeg[i])
                    diff++;
            }
        }
        memset(used, 0, sizeof(used));
        int ans = 0;
        //printf("%d %d %d\n", sn, en, diff);
        if(sn == 1 && en == 1 && diff == 0) {
            ans = 1;
            color(st);
            for(i = 0; i < 26; i++) {
                if(indeg[i] != 0 || outdeg[i] != 0) {
                    if(used[i] == 0)
                        ans = 0;
                }
            }
        } else {
            if(sn == 0 && en == 0 && diff == 0) {
                ans = 1;
                //puts("here");
                for(i = 0; i < 26; i++)
                    if(indeg[i])
                        st = i;
                color(st);
                for(i = 0; i < 26; i++) {
                    if(indeg[i] != 0 || outdeg[i] != 0) {
                        if(used[i] == 0)
                            ans = 0;
                    }
                }
            } else
                ans = 0;
        }
        if(ans)
            puts("Ordering is possible.");
        else
            puts("The door cannot be opened.");
    }
    return 0;
}
