#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>
#include <map>
using namespace std;
struct MAXHEAP {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b) const {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    }
};
struct MINHEAP {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b) const {
        return a.first > b.first || (a.first == b.first && a.second < b.second);
    }
};
int main() {
    int testcase, n;
    int item, price;
    char cmd[128], share[128], at[128];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        priority_queue< pair<int, int>, vector<pair<int,int> >, MAXHEAP > buy; // max-heap
        priority_queue< pair<int, int>, vector<pair<int,int> >, MINHEAP > sell; // min-heap
        int stock = -1;
        for (int i = 0; i < n; i++) {
            scanf("%s %d %s %s %d", cmd, &item, share, at, &price);
            if (cmd[0] == 'b')
                buy.push(make_pair(price, item));
            if (cmd[0] == 's')
                sell.push(make_pair(price, item));
            while (!buy.empty() && !sell.empty()) {
                pair<int, int> p, q;
                p = buy.top();
                q = sell.top();
                if (p.first < q.first)
                    break;
                buy.pop(), sell.pop();
                int change = min(p.second, q.second);
                stock = q.first;
//                printf("change %d\n", change);
                p.second -= change, q.second -= change;
                if (p.second)
                    buy.push(p);
                if (q.second)
                    sell.push(q);
            }
            //            printf("%d %d\n", item, price);
            if (!sell.empty())  printf("%d ", sell.top().first);
            else                printf("- ");
            if (!buy.empty())   printf("%d ", buy.top().first);
            else                printf("- ");
            if (stock != -1)    printf("%d\n", stock);
            else                printf("-\n");
        }
    }
    return 0;
}
/*
 2
 6
 buy 10 shares at 100
 sell 1 shares at 120
 sell 20 shares at 110
 buy 30 shares at 110
 sell 10 shares at 99
 buy 1 shares at 120
 6
 sell 10 shares at 100
 buy 1 shares at 80
 buy 20 shares at 90
 sell 30 shares at 90
 buy 10 shares at 101
 sell 1 shares at 80
 
 - 100 -
 120 100 -
 110 100 -
 120 110 110
 120 100 99
 - 100 120
 100 - -
 100 80 -
 100 90 -
 90 80 90
 100 80 90
 100 - 80
 */