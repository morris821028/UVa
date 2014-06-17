#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

int main() {
    int n;
    char s[30];
    while(scanf("%d", &n) == 1) {
        set<string> d;
        while(n--) {
            scanf("%s", s);
            d.insert(s);
        }
        scanf("%d", &n);
        while(n--) {
            scanf("%s", s);
            if(d.find(s) != d.end())
                puts("yes");
            else {
                puts("no");
                d.insert(s);
            }
        }
    }
    return 0;
}
