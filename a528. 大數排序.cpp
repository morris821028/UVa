#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[1000][105], sl[1000];
int a[1000];
bool cmp(int x, int y) {
    static int i;
    if(s[x][0] == '-') {
        if(s[y][0] != '-')    return true;
        if(sl[x] != sl[y])  return sl[x] > sl[y];
        for(i = 1; i < sl[x]; i++)
            if(s[x][i] != s[y][i])
                return s[x][i] > s[y][i];
        return false;
    }
    if(s[y][0] == '-')  return false;
    if(sl[x] != sl[y])  return sl[x] < sl[y];
    for(i = 0; i < sl[x]; i++)
        if(s[x][i] != s[y][i])
            return s[x][i] < s[y][i];
    return false;
}
int main() {
    int n, i;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%s", s[i]), a[i] = i, sl[i] = strlen(s[i]);
        sort(a, a+n, cmp);
        for(i = 0; i < n; i++)
            puts(s[a[i]]);
    }
    return 0;
}
