#include <stdio.h>
#include <string.h>

int main() {
    int t, n, i, j;
    char org[210][88], des[210][88];
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        getchar();
        for(i = 0; i < n; i++)
            gets(org[i]);
        for(i = 0; i < n; i++)
            gets(des[i]);
        for(i = n-1, j = n-1; i >= 0; i--)
            if(!strcmp(org[i], des[j]))
                j--;
        for(; j >= 0; j--)
            puts(des[j]);
        puts("");
    }
    return 0;
}
