#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
#include <assert.h>
using namespace std;

struct Frac {
    long long x, y;
    Frac(long long a = 0, long long b = 1) {
        x = a, y = b;
        normal();
    }
    void normal() {
        if (y < 0)  x = -x, y = -y;
        long long g = llgcd(x, y);
        x /= g, y /= g;
        if (y < 0)  x = -x, y = -y;
    }
    long long llgcd(long long x, long long y) const {
    	if (x == 0)	return y;
    	if (y == 0)	return x;
        long long t;
        while (x%y)
            t = x, x = y, y = t % y;
        return y;
    }
    Frac operator-(const Frac &a) const {
        long long va = 0, vb = a.y / llgcd(y, a.y) * y;
        va = vb / y * x - vb / a.y * a.x;
        return Frac(va, vb);
    }
    Frac operator+(const Frac &a) const {
        long long va = 0, vb = a.y / llgcd(y, a.y) * y;
        va = vb / y * x + vb / a.y * a.x;
        return Frac(va, vb);
    }
    Frac operator*(const Frac a) const {
        long long g1 = llgcd(x, a.y), g2 = llgcd(a.x, y);
        long long va = 0, vb = 0;
        va = (x / g1) * (a.x / g2);
        vb = (y / g2) * (a.y / g1);
        return Frac(va, vb);
    }
    Frac operator/(const Frac a) const {
        long long g1 = llgcd(y, a.y), g2 = llgcd(x, a.x);
        long long va = 0, vb = 0;
        va = (a.y / g1) * (x / g2);
        vb = (y / g1) * (a.x / g2);
        return Frac(va, vb);
    }
    bool operator==(const Frac &a) const {
        return x - a.x == 0 && y - a.y == 0;
    }
    bool operator<(const Frac &a) const {
        return x * a.y < a.x * y;
    }
    void print() {
        if (y == 1)
            printf("%lld", x);
        else
            printf("%lld/%lld", x, y);
    }
};

Frac getX(char s[]) {
    int a = 0, b = 0;
    for (int i = 0; s[i]; i++) {
        a += (s[i] - '0')%2 == 0;
        b ++;
    }
    return Frac(a, b);
}
Frac getY(char s[]) {
    int a = 0, b = 0;
    for (int i = 0; s[i]; i++) {
        int d = s[i] - '0';
        if (d == 2 || d == 3 || d == 5 || d == 7)
            a++;
        b ++;
    }
    return Frac(a, b);
}
Frac getZ(char s[]) {
    int a = 0, b = 0;
    for (int i = 0; s[i]; i++) {
        int d = s[i] - '0';
        if (d < 5 && d%2 == 1)
            a++;
        b ++;
    }
    return Frac(a, b);
}

int getTestXYZ(char s[], Frac &x, Frac &y, Frac &z) {
    int n = (int) strlen(s);
	if (s[1%n] == '0' || s[3%n] == '0' || s[5%n] == '0')
		return 0;
    x = Frac(s[0%n] - '0', s[1%n] - '0');
    y = Frac(s[2%n] - '0', s[3%n] - '0');
    z = Frac(s[4%n] - '0', s[5%n] - '0');
	return 1;
}
int isprime(int x) {
    if (x == 1)
        return 0;
    for (int i = 2; i * i <= x; i++)
        if (x%i == 0)
            return 0;
    return 1;
}
int main() {
    char s[64];
    while (scanf("%s", s) == 1) {
        Frac x = getX(s), y = getY(s), z = getZ(s);
        Frac rx, ry, rz;
        x.print(), printf(" ");
        y.print(), printf(" ");
        z.print(), printf("\n");
		
		assert(x == Frac(0, 1) || x == Frac(1, 2) || x == Frac(1, 1));
		assert(y == Frac(0, 1) || y == Frac(1, 2) || y == Frac(1, 1));
		assert(z == Frac(0, 1) || z == Frac(1, 2) || z == Frac(1, 1));
        int f = getTestXYZ(s, rx, ry, rz);
        if (!f) {
        	assert(false);
        	continue;
        }
//        rx.print(), printf(" ");
//        ry.print(), printf(" ");
//        rz.print(), printf("\n");
        
        Frac dot = rx * x + ry * y + rz * z;
        if (!isprime((int)dot.x) && dot.x != 1) {
            puts("SAFE");
        } else {
            puts("FATAL");
        }
//        dot.print();
//        puts("");
    }
    return 0;
}

/*
 18540
 385
 1222 
 123456
 1234
 24556789
 74974652
*/
