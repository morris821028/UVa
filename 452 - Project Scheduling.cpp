#include <stdio.h>
#include <string.h>

int main() {
    int t, v;
    char line[100], h[2];
    scanf("%d ", &t);
    while(t--) {
        int map[26][26] = {}, day[26] = {}, mt[26] = {};
        int i, j, done[26] = {};
        while(gets(line)) {
            if(line[0] == '\0')
                break;
            sscanf(line, "%s %d", h, &v);
            j = h[0]-'A', done[j] = 1;
            day[j] = v;
            for(i = strlen(line)-1; i >= 0; i--) {
                if(line[i] < 'A' || line[i] > 'Z')
                    break;
                map[j][mt[j]++] = line[i]-'A';
            }
        }
        int fin[26] = {}, used[26] = {};
        int max, ans = 0;
        while(1) {
            int flag = 0;
            for(i = 0; i < 26; i++) {
                if(used[i] == 0 && done[i] == 1) {
                    max = 0;
                    for(j = 0; j < mt[i]; j++) {
                        if(used[map[i][j]] == 0)
                            break;
                        if(fin[map[i][j]] > max)
                            max = fin[map[i][j]];
                    }
                    if(j == mt[i]) {
                        fin[i] = max+day[i];
                        if(fin[i] > ans)
                            ans = fin[i];
                        used[i] = 1;
                        flag = 1;
                    }
                }
            }
            if(flag == 0)
                break;
        }
        printf("%d\n", ans);
        if(t)
            puts("");
    }
    return 0;
}
