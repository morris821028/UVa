#include <stdio.h>

int main() {
    int t, Case = 0;
    int s[] = {1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,4,1,2,3,1,2,3,4};
    char str[1000];
    scanf("%d", &t);
    getchar();
    while(t--) {
        gets(str);
        int ans = 0, i;
        for(i = 0; str[i]; i++) {
            if(str[i] == ' ')
                ans++;
            else
                ans += s[str[i]-'a'];
        }
        printf("Case #%d: %d\n", ++Case, ans);
    }
    return 0;
}
