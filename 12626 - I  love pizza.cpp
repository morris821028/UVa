#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int t;
    char s[605];
    scanf("%d", &t);
    while(t--) {
        scanf("%s", s);
        int ascii[128] = {};
        for(int i = 0; s[i]; i++)
            ascii[s[i]]++;
        int ret = 0xffff;
        ret = min(ret, ascii['M']/1);
        ret = min(ret, ascii['A']/3);
        ret = min(ret, ascii['R']/2);
        ret = min(ret, ascii['G']/1);
        ret = min(ret, ascii['T']/1);
        ret = min(ret, ascii['I']/1);
        printf("%d\n", ret);
    }
    return 0;
}
