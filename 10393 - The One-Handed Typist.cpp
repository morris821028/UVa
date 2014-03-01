#include <stdio.h>
#include <set>
#include <iostream>
using namespace std;
int main() {
    int type[256] = {};
    type['q'] |= 1<<1, type['a'] |= 1<<1, type['z'] |= 1<<1;
    type['w'] |= 1<<2, type['s'] |= 1<<2, type['x'] |= 1<<2;
    type['e'] |= 1<<3, type['d'] |= 1<<3, type['c'] |= 1<<3;
    type['r'] |= 1<<4, type['f'] |= 1<<4, type['v'] |= 1<<4;
    type['t'] |= 1<<4, type['g'] |= 1<<4, type['b'] |= 1<<4;
    type[' '] |= 1<<5;
    type[' '] |= 1<<6;
    type['y'] |= 1<<7, type['h'] |= 1<<7, type['n'] |= 1<<7;
    type['u'] |= 1<<7, type['j'] |= 1<<7, type['m'] |= 1<<7;
    type['i'] |= 1<<8, type['k'] |= 1<<8, type[','] |= 1<<8;
    type['o'] |= 1<<9, type['l'] |= 1<<9, type['.'] |= 1<<9;
    type['p'] |= 1<<10, type[';'] |= 1<<10, type['/'] |= 1<<10;
    int n, m, i;
    while(scanf("%d %d", &n, &m) == 2) {
        int x, notuse = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            notuse |= 1<<x;
        }
        int anslen = 0;
        char s[105];
        set<string> output;
        while(m--) {
            scanf("%s", s);
            int flag = 1;
            for(i = 0; s[i]; i++) {
                flag &= (type[s[i]] - (type[s[i]]&notuse) != 0);
            }
            if(flag && i >= anslen) {
                if(i > anslen)
                    output.clear();
                anslen = i;
                output.insert(s);
            }
        }
        printf("%d\n", output.size());
        for(set<string>::iterator it = output.begin();
            it != output.end(); it++)
            puts((*it).c_str());
    }
    return 0;
}
