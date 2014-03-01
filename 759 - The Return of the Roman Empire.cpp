#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

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
    int n;
    char *str, in[50];
    map<string, int> ch1;
    for(n = 1; n < 4000; n++) {
        str = toRoman(n);
        ch1[str] = n;
        delete[] str;
    }
    while(gets(in)) {
        if(in[0] == '\0')
            puts("0");
        else if(ch1[in] == 0)
            cout << "This is not a valid number" << endl;
        else
            cout << ch1[in] << endl;
    }
    return 0;
}
