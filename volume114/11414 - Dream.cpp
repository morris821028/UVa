#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
int main() {
    int t, n, deg[1000];
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &deg[i]);
        sort(deg, deg+n, greater<int>());
        int err = 0;
        for(i = 0; i < n; i++) {
            if(i+deg[i] < n)
                for(j = deg[i]; j >= 1; j--)
                    deg[j+i]--, deg[i]--;
            if(deg[i]) {
                err = 1;
                break;
            }
            sort(deg+i+1, deg+n, greater<int>());
        }
        puts(err ? "No" : "Yes");
    }
    return 0;
}
