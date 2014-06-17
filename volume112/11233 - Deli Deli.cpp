#include <stdio.h>
#include <map>
#include <iostream>
#include <string.h>
using namespace std;
int main() {
    int n, m;
    char a[100], b[100];
    while(scanf("%d %d", &n, &m) == 2) {
        map<string, string> R;
        while(n--) {
            scanf("%s %s", a, b);
            R[a] = b;
        }
        while(m--) {
            scanf("%s", a);
            if(R.find(a) != R.end()) {
                printf("%s\n", R[a].c_str());
                continue;
            }
            int len = strlen(a);
            if(a[len-1] == 'y' && a[len-2] != 'a' && a[len-2] != 'e'
               && a[len-2] != 'i'&& a[len-2] != 'o'&& a[len-2] != 'u') {
                a[len-1] = 'i', a[len] = 'e', a[len+1] = 's';
                a[len+2] = '\0';
            } else if(a[len-1] == 'o' || a[len-1] == 's' || a[len-1] == 'x') {
                a[len] = 'e';
                a[len+1] = 's';
                a[len+2] = '\0';
            } else if(len >= 2 && ((a[len-2] == 'c' && a[len-1] == 'h') ||
                                   (a[len-2] == 's' && a[len-1] == 'h'))) {
                a[len] = 'e';
                a[len+1] = 's';
                a[len+2] = '\0';
            } else
                a[len] = 's', a[len+1] = '\0';
            puts(a);
        }
    }
    return 0;
}
