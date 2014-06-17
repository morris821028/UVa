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
    int n, DP[101][5] = {};

    char *str;
    for(n = 1; n <= 100; n++) {
        str = toRoman(n);
        for(int i = 0; i < 5; i++)
            DP[n][i] = DP[n-1][i];
        for(int i = 0; str[i]; i++) {
            switch(str[i]) {
                case 'I':DP[n][0]++;break;
                case 'V':DP[n][1]++;break;
                case 'X':DP[n][2]++;break;
                case 'L':DP[n][3]++;break;
                case 'C':DP[n][4]++;break;
            }
        }
        delete[] str;
    }
    while(scanf("%d", &n) == 1 && n) {
        printf("%d: %d i, %d v, %d x, %d l, %d c\n", n, DP[n][0], DP[n][1], DP[n][2], DP[n][3], DP[n][4]);
    }
    return 0;
}
