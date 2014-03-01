#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    string a = "h0", b = "h1", c = "h2", d = "h3", e = "h4";
    string f, tmp;
    int i;
    for(i = 0; i < 5; i++) {
        f = b+ "+" +c;
        char j = i+'0';
        tmp = "4*(" + a + ")"+"+"+f+"+"+e+"+k"+"+word["+j+"]";
        e = d, d = c, c = "8*(" + b + ")", b = a, a = tmp;
    }
    cout << "h0+"+a << endl<<endl;
    cout << "h1+"+b << endl<<endl;
    cout << "h2+"+c << endl<<endl;
    cout << "h3+"+d << endl<<endl;
    cout << "h4+"+e << endl<<endl;
    return 0;
}
