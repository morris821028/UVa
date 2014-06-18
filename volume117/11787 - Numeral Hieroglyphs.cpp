#include <stdio.h>

int main() {
    int t;
    char s[501];
    scanf("%d ", &t);
    while(t--) {
        gets(s);
        bool flag1 = false, flag2 = false;
        char ch[] = {'M','T','F','P','S','U','B'};
        long nu[] = {1000000,100000,10000,1000,100,10,1};
        int i, j, k, ans1 = 0, ans2 = 0;
        for(i = 0, j = 0, k = 0; i < 7; i++) {
            int cnt = 0;
            while(s[j] == ch[i]) {
                cnt++, j++;
                ans1 += nu[i];
                if(cnt > 9) flag1 = true;
            }
            cnt = 0;
            while(s[k] == ch[6-i]) {
                cnt++, k++;
                ans2 += nu[6-i];
                if(cnt > 9) flag2 = true;
            }
        }
        if(s[j] != '\0') flag1 = true;
        if(s[k] != '\0') flag2 = true;
        if(flag1 && flag2)
            puts("error");
        else
            printf("%d\n", flag2 ? ans1 : ans2);
    }
    return 0;
}
