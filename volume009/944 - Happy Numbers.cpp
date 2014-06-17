#include <stdio.h>
#include <set>
using namespace std;
int happy[100000] = {};
void solve() {
    int i;
    for(i = 1; i < 100000; i++) {
        int l = 0, n = i, tmp;
        set<int> s;
        while(n != 1) {
            l++;
            tmp = 0;
            while(n) {
                tmp += (n%10)*(n%10);
                n /= 10;
            }
            n = tmp;
            if(s.find(n) != s.end())
                break;
            s.insert(n);
        }
        if(n == 1)
            happy[i] = l+1;
    }
}
int main() {
    solve();
    int flag = 0, L, H;
    while(scanf("%d %d", &L, &H) == 2) {
        if(flag)
            puts("");
        flag = 1;
        for(int i = L; i <= H; i++) {
            if(happy[i])
                printf("%d %d\n", i, happy[i]);
        }
    }
    return 0;
}
