#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n, m, l, r, i;
    while(scanf("%d %d", &n, &m) == 2) {
        vector<int> vec;
        for(i = 1; i <= n; i++)
            vec.push_back(i);
        while(m--) {
            scanf("%d %d", &l, &r), l--;
            reverse(&vec[l], &vec[r]);
        }
        for(i = 0; i < n; i++)
            printf("%s%d", i ? " " : "", vec[i]);
        puts("");
    }
    return 0;
}
