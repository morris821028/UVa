#include <stdio.h>
#include <iostream>
using namespace std;
string int2ch(int n) {
    static int i, flag, t;
    static int v[6] = {'|', 'n', '9', '8', 'r'};
    string r = "";
    flag = 0;
    for(i = 0; i < 6; i++) {
        if(n%10) {
            if(flag)    r += ' ';
            t = n%10;
            while(t)    r += v[i], t--;
            flag = 1;
        }
        n /= 10;
    }
    return r;
}
int main() {
    int ch2int[127] = {};
    ch2int['|'] = 1;
    ch2int['n'] = 10;
    ch2int['9'] = 100;
    ch2int['8'] = 1000;
    ch2int['r'] = 10000;
    char a[200], b[200];
    int i;
    while(gets(a)) {
        gets(b);
        int na = 0, nb = 0, ans;
        for(i = 0; a[i]; i++)
            na += ch2int[a[i]];
        for(i = 0; b[i]; i++)
            nb += ch2int[b[i]];
        ans = na*nb;
        for(i = 0; (nb>>i) > 0; i++) {
            string line = int2ch(1<<i);
            if((nb>>i)&1)
                line += " *";
            while(line.length() < 34)
                line += ' ';
            line += int2ch((1<<i)*na);
            cout << line << endl;
        }
        printf("The solution is: %s\n", int2ch(ans).c_str());
    }
    return 0;
}
