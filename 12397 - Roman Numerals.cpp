#include <stdio.h>
char* toRoman(int num) {
    const char rcode[13][3] = {"M", "CM", "D", "CD", "C", "XC", "L",
                        "XL", "X", "IX", "V", "IV", "I"};
    const int val[13] = {1000, 900, 500, 400, 100, 90, 50,
                        40, 10, 9, 5, 4, 1};
    char *roman = new char[30], idx = 0;
    int i;
    for(i = 0; i < 13; i++) {
        while(num >= val[i]) {
            num -= val[i];
            roman[idx++] = rcode[i][0];
            if(rcode[i][1] != '\0')
                roman[idx++] = rcode[i][1];
        }
    }
    roman[idx] = '\0';
    return roman;
}
int main() {
    int n, i;
    char cost[128] = {};
    cost['I'] = 1;
    cost['V'] = 2;
    cost['X'] = 2;
    cost['L'] = 2;
    cost['C'] = 2;
    cost['D'] = 3;
    cost['M'] = 4;
    while(scanf("%d", &n) == 1) {
        char *p = toRoman(n);
        n = 0;
        for(i = 0; p[i]; i++)
            n += cost[p[i]];
        printf("%d\n", n);
        delete[] p;
    }
}
