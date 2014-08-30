#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <vector>
#include <stack>
using namespace std;

int n;
int h[1048576], a[1048576];
int main() {
    while(scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            scanf("%d", &h[i]), a[i] = h[i];
        
        stack< pair<int, int> > stk;
        for (int i = 0; i < n; i++) {
            if (!stk.empty()) {
                stk.top().second = min(stk.top().second, h[i]);
            }
            while (!stk.empty() && stk.top().first <= h[i]) {
                pair<int, int> p = stk.top();
                stk.pop();
                if (!stk.empty())
                    stk.top().second = min(stk.top().second, p.second);
            }
            if (!stk.empty()) {
                a[i] = min(a[i], h[i] - stk.top().second);
            }
            stk.push(make_pair(h[i], h[i]));
        }
        
        while (!stk.empty())
            stk.pop();
            
        for (int i = n - 1; i >= 0; i--) {
            if (!stk.empty()) {
                stk.top().second = min(stk.top().second, h[i]);
            }
            while (!stk.empty() && stk.top().first <= h[i]) {
                pair<int, int> p = stk.top();
                stk.pop();
                if (!stk.empty())
                    stk.top().second = min(stk.top().second, p.second);
            }
            if (!stk.empty()) {
                a[i] = min(a[i], h[i] - stk.top().second);
            }
            stk.push(make_pair(h[i], h[i]));
        }
        
        int f = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] >= 150000) {
                if (f++) printf(" ");
                printf("%d", i + 1);
            }
        }
        puts("");
	}
    return 0;
}
/*
 5
 0 10000 100000 884813 0
 7
 0 100000 0 200000 180000 200000 0
 */