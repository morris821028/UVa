#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        string ret[n];
        string s, foo;
        int i, idx = 0, len;
        for(i = 0; i < n; i++) {
            cin >> s >> foo;
            len = foo.length();
            while(len) {
                if(ret[idx] == "")
                    len--;
                idx++;
                if(idx >= n)    idx = 0;
            }
            ret[(idx-1+n)%n] = s;
        }
        for(i = 0; i < n; i++) {
            if(i)   putchar(' ');
            cout << ret[i];
        }
        puts("");
    }
    return 0;
}
