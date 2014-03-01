#include <stdio.h>
#include <string.h>
const char s[][4] = {"XXL", "XL", "L", "M", "S", "XS"};
int code(const char *str) {
    static int i;
    for(i = 0; i < 6; i++)
        if(!strcmp(s[i], str))
            return i;
}
int map[30][2], flag, used[6];
int n, m, t;
void dfs(int idx) {
    if(flag)
        return;
    if(idx == m) {
        flag = 1;
        return;
    }
    if(used[map[idx][0]] > 0) {
        used[map[idx][0]]--;
        dfs(idx+1);
        used[map[idx][0]]++;
    }
    if(used[map[idx][1]] > 0) {
        used[map[idx][1]]--;
        dfs(idx+1);
        used[map[idx][1]]++;
    }
}
int main() {
    char str[20];
    int i, num;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        n = n/6;
        for(i = 0; i < m; i++) {
            scanf("%s", str);
            num = code(str);
            map[i][0] = num;
            scanf("%s", str);
            num = code(str);
            map[i][1] = num;
        }
        for(i = 0; i < 6; i++)
            used[i] = n;
        flag = 0;
        dfs(0);
        if(flag)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
