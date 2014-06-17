#include <stdio.h>

int main() {
    char A[105], B[105];
    while(scanf("%s %s", A, B) == 2) {
        int a[128] = {}, b[128] = {}, cnt[128] = {};
        int i;
        for(i = 0; A[i]; i++)
            a[A[i]]++;
        for(i = 0; B[i]; i++)
            b[B[i]]++;
        for(i = 'A'; i <= 'Z'; i++)
            cnt[a[i]]++, cnt[b[i]]--;
        for(i = 0; i <= 100; i++)
            if(cnt[i])  break;
        if(i == 101)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
