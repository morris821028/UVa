#include <stdio.h>
int func[8];
int target[50], origin[50];
int ID, n, found;
char s[50];
void dfs(int idx) {
    if(found)   return;
    int i, j;
    if(idx == n-1) {
        i = (origin[n-2]<<2)|(origin[n-1]<<1)|(origin[0]<<0);
        j = (origin[n-1]<<2)|(origin[0]<<1)|(origin[1]<<0);
        if(target[idx] == func[i] && target[0] == func[j])
            found = 1;
        return;
    }
    for(i = 0; i < 8; i++) {
        if(func[i] == target[idx] && ((i>>2)&1) == origin[idx-1] && ((i>>1)&1) == origin[idx]) {
            origin[idx+1] = (i>>0)&1;
            dfs(idx+1);
            if(found)   return;
        }
    }
}
int main() {
    int i;
    while(scanf("%d %d %s", &ID, &n, s) == 3) {
        for(i = 0; i < n; i++)
            target[i] = s[i]-'0';
        for(i = 0; i < 8; i++)
            func[i] = (ID>>i)&1;
        found = 0;
        for(i = 0; i < 8; i++) {
            if(func[i] == target[0]) {
                origin[0] = (i>>1)&1;
                origin[1] = (i>>0)&1;
                dfs(1);
            }
        }
        if(found)
            puts("REACHABLE");
        else
            puts("GARDEN OF EDEN");
    }
    return 0;
}
