#include <stdio.h>
#include <string.h>
int table[5][5] = {};
int letter[26][2];
void fillTable(char s[]) {
    int idx = 0;
    int i, j, k;
    int used[26] = {};
    for(i = 0; s[i]; i++) {
        if(s[i] >= 'a' && s[i] <= 'z') {
            if(s[i] == 'q') continue;
            if(used[s[i]-'a'] == 0) {
                used[s[i]-'a'] = 1;
                table[idx/5][idx%5] = s[i] - 'a';
                idx++;
            }
        }
    }
    for(i = 0; i < 26; i++) {
        if(used[i] == 0 && i != 'q'-'a') {
            table[idx/5][idx%5] = i;
            idx++;
        }
    }
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            letter[table[i][j]][0] = i;
            letter[table[i][j]][1] = j;
        }
    }
}
void encrypted(char a, char b) {
    a -= 'a', b -= 'a';
    if(letter[a][0] == letter[b][0]) {
        putchar(table[letter[a][0]][(letter[a][1]+1)%5]+'A');
        putchar(table[letter[a][0]][(letter[b][1]+1)%5]+'A');
    } else if(letter[a][1] == letter[b][1]) {
        putchar(table[(letter[a][0]+1)%5][letter[a][1]]+'A');
        putchar(table[(letter[b][0]+1)%5][letter[a][1]]+'A');
    } else {
        putchar(table[letter[a][0]][letter[b][1]]+'A');
        putchar(table[letter[b][0]][letter[a][1]]+'A');
    }
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while(getchar() != '\n');
    char s[1024];
    while(testcase--) {
        gets(s);
        fillTable(s);
        gets(s);
        int i, j, len = strlen(s);
        char a, b;
        for(i = 0, j = 0; i < len; i++)
            if(s[i] >= 'a' && s[i] <= 'z')
                s[j++] = s[i];
        s[j] = '\0';
        len = strlen(s);
        for(i = 0; i < len; i += 2) {
            a = s[i];
            if(i+1 < len) {
                b = s[i+1];
                if(a == b)
                    b = 'x', i--;
            }
            else            b = 'x';
            encrypted(a, b);
        }
        puts("");
    }
    return 0;
}
