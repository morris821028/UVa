#include <stdio.h>
#include <string.h>
char code[10000][15], tmp[15];
int tot = 0;
void dfs(int idx, int n) {
    if(idx == n) {
        tmp[n] = '\0';
        memcpy(code[tot], tmp, sizeof(tmp));
        tot++;
        return;
    }
    tmp[idx] = '0';
    dfs(idx+1, n);
    tmp[idx] = '1';
    dfs(idx+1, n);
}
void build() {
    int i;
    for(i = 1; i < 8; i++)
        dfs(0, i), tot--;
}
int main() {
    build();
    char msg[1000];
    int i;
    while(gets(msg)) {
        int a, b, c, num;
        while(1) {
            while(a = getchar()) {
                if(a == '1' || a == '0')
                break;
            }
            while(b = getchar()) {
                if(b == '1' || b == '0')
                break;
            }
            while(c = getchar()) {
                if(c == '1' || c == '0')
                break;
            }
            a -= '0', b -= '0', c -= '0';
            num = a<<2 | b<<1 | c;
            if(num == 0)
                break;
            while(1) {
                char tmp[15], idx = 0;
                int cnt = num;
                while(cnt--) {
                    while(a = getchar()) {
                        if(a == '1' || a == '0')
                            break;
                    }
                    tmp[idx++] = a;
                }
                tmp[idx] = '\0';
                for(i = 0; i < tot; i++) {
                    if(!strcmp(code[i], tmp)) {
                        printf("%c", msg[i]);
                        break;
                    }
                }
                if(i == tot)
                    break;
            }
        }
        puts("");
        gets(msg);
    }
    return 0;
}
