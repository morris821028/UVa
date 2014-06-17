#include <stdio.h>

int main() {
    char a[20], b[1000005];
    int i, j;
    gets(a);
    gets(b);
    for(i = 0; a[i]; i++) {
        if(a[i] >= 'A' && a[i] <= 'Z')
            a[i] = a[i]-'A'+'a';
    }
    for(i = 0; b[i]; i++) {
        if(b[i] >= 'A' && b[i] <= 'Z')
            b[i] = b[i]-'A'+'a';
    }
    int cnt = 0, res = 0;
    for(i = 0; b[i]; i++) {
        if(b[i] != ' ') {
            for(j = 0; a[j] && b[i+j]; j++)
                if(a[j] != b[i+j])
                    break;
            if(a[j] == '\0' && (b[i+j] == ' ' || b[i+j] == '\0')) {
                if(!cnt)    res = i;
                cnt++;
            }
            while(b[i] != ' ')  i++;
        }
    }
    if(cnt)
        printf("%d %d\n", cnt, res);
    else
        puts("-1");
    return 0;
}
