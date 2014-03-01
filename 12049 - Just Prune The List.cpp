#include <stdio.h>
#include <stdlib.h>
#include <map>
using namespace std;
int main() {
    scanf("%*d");
    int n, m, x;
    while(scanf("%d %d", &n, &m) == 2) {
        map<int, int> r;
        while(n--)
            scanf("%d", &x), r[x]++;
        while(m--)
            scanf("%d", &x), r[x]--;
        x = 0;
        for(map<int,int>::iterator it = r.begin();
            it != r.end(); it++)
            x += abs(it->second);
        printf("%d\n", x);
    }
    return 0;
}
