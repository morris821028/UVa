#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char s[1<<16];
    int T, f[26][26] = {}, used[26] = {};
    scanf("%d", &T);
    while (scanf("%s", s) == 1) {
        for (int i = 1; s[i]; i++)
            f[s[i-1]-'a'][s[i]-'a']++;
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++)
            printf("%d%c", f[i][j], " \n"[j==25]);
    }
    
    int u = 0, v = 0, mx = -1;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (f[i][j] > mx)
                mx = f[i][j], u = i, v = j;
        }
    }
    printf("%c%c", u+'a', v+'a');
    used[u] = used[v] = 1;
    while ((u = v) >= 0) {
        v = -1, mx = -1;
        for (int i = 0; i < 26; i++) {
            if (f[u][i] > mx && used[i] == 0)
                mx = f[u][i], v = i;
        }
        
        if (mx > T)
            putchar(v+'a'), used[v] = 1;
        else
            v = -1;
    }
    return 0;
}
/*
 
*/

