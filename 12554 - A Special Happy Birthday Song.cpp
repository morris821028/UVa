#include <stdio.h>

int main() {
    char song[][20] = {
        "Happy", "birthday", "to", "you", "Happy", "birthday", "to", "you"
        , "Happy", "birthday", "to", "Rujia", "Happy", "birthday", "to", "you"
    };
    char name[101][101];
    int n, i, j, flag = 0, end = 0;
    scanf("%d", &n);
    for(i = 0; i < n; i++)  scanf("%s", &name[i]);
    i = 0, j = 0;
    while(1) {
        printf("%s: %s\n", name[i], song[j]);
        if(i == n-1)
            flag = 1;
        if(j == 15 && flag)
            break;
        i++, j++;
        if(i >= n)  i = 0;
        if(j >= 16) j = 0;
    }
    return 0;
}
/*
3
Mom
Dad
Girlfriend
*/
