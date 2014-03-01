#include <stdio.h>
char table[14][11] = {
    "0111001111",
    "0111001110",
    "0111001100",
    "0111001000",
    "0111000000",
    "0110000000",
    "0100000000",
    "0010000000",
    "1111001110",
    "1111001100",
    "1111001000",
    "1111000000",
    "1110000000",
    "1100000000"
};
int main() {
    int t;
    char in[205];
    int mapped[128];
    mapped['c'] = 0, mapped['d'] = 1;
    mapped['e'] = 2, mapped['f'] = 3;
    mapped['g'] = 4, mapped['a'] = 5;
    mapped['b'] = 6, mapped['C'] = 7;
    mapped['D'] = 8, mapped['E'] = 9;
    mapped['F'] = 10, mapped['G'] = 11;
    mapped['A'] = 12, mapped['B'] = 13;
    scanf("%d", &t);
    getchar();
    while(t--) {
        gets(in);
        int i, j, ans[10] = {}, press[10] = {};
        for(i = 0; in[i]; i++) {
            for(j = 0; j < 10; j++) {
                if(table[mapped[in[i]]][j] == '1') {
                    if(press[j] == 0)
                        ans[j] += table[mapped[in[i]]][j] == '1';
                    press[j] = 1;
                } else {
                    press[j] = 0;
                }
            }
        }
        for(i = 0; i < 10; i++) {
            if(i)
                printf(" ");
            printf("%d", ans[i]);
        }
        puts("");
    }
    return 0;
}
