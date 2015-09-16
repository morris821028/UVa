#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
struct BigDecimal {
    string a, b;
    int sign;
    int read() {
        char s[1024];
        int f = scanf("%s", s) == 1;
        sign = 1;
        for (int i = 0; s[i]; i++) {
            if (s[i] == '.') {
                s[i] = '\0';
                if (s[0] == '-')
                    a = s+1, sign = -1;
                else if (s[0] == '+')
                    a = s+1, sign = 1;
                else
                    a = s, sign = 1;
                b = s+i+1;
            }
        }
        return f;
    }
    int cmp(const BigDecimal &x) const {
        if (sign != x.sign)
            return sign < x.sign ? -1 : 1;
        if (sign == 1) {
            if (a.length() != x.a.length())
                return a.length() < x.a.length() ? -1 : 1;
            for (int i = 0; i < a.length(); i++) {
                if (a[i] != x.a[i])
                    return a[i] < x.a[i] ? -1 : 1;
            }
            for (int i = 0; i < max(b.length(), x.b.length()); i++) {
                int p = '0', q = '0';
                if (i < b.length())     p = b[i];
                if (i < x.b.length())   q = x.b[i];
                if (p != q)
                    return p < q ? -1 : 1;
            }
        } else {
            if (a.length() != x.a.length())
                return a.length() < x.a.length() ? 1 : -1;
            for (int i = 0; i < a.length(); i++) {
                if (a[i] != x.a[i])
                    return a[i] < x.a[i] ? 1 : -1;
            }
            for (int i = 0; i < max(b.length(), x.b.length()); i++) {
                int p = '0', q = '0';
                if (i < b.length())     p = b[i];
                if (i < x.b.length())   q = x.b[i];
                if (p != q)
                    return p < q ? 1 : -1;
            }
        }
        return 0;
    }
};
int main() {
    int cases = 0;
    BigDecimal a, b;
    while (a.read()) {
        b.read();
        printf("Case %d: ", ++cases);
        int c = a.cmp(b);
        if (c == 0)
            puts("Same");
        else if (c == 1)
            puts("Bigger");
        else
            puts("Smaller");
    }
    return 0;
}