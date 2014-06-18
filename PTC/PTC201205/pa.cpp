#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
using namespace std;
char str[10000060];
void tosmall(char s[]) {
    int i;
    for(i = 0; s[i]; i++)
        if(s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i]-'A'+'a';
}
int main() {
    char name[21][50] = {"Richmond", "Ward", "Young", "Joss", "Robertson", "Larsen", "Bunning", "Koufax",
"Hunter", "Barker", "Witt", "Browning", "Martinez", "Rogers","Wells", "Cone", "Johnson", "Buehrle", "Braden", "Halladay", "Humber"};
    int namel[21];
    int t, n;
    scanf("%d ", &n);
    int i;
    for(i = 0; i < 21; i++)
        tosmall(name[i]), namel[i] = strlen(name[i]);
    while(n--) {
        gets(str);
        int ans = 0, slen =strlen(str);
        tosmall(str);
        int j, tmp;
        for(i = 0; i < slen; i++) {
            for(j = 0; j < 21; j++) {
                if(i+namel[j] > slen)
                    continue;
                tmp = str[i+namel[j]];
                str[i+namel[j]] = '\0';
                //system("pause");
                if(!strcmp(str+i, name[j]))
                    ans++;
                str[i+namel[j]] = tmp;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
