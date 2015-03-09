#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct Pt {
    int x, y;
    bool operator<(const Pt a) const {
        if(a.x != x)
            return x < a.x;
        return y < a.y;
    }
};
int main() {
    int n, i, j, cases = 0;
    Pt p[50000];
    //freopen("in.txt", "r+t", stdin);
	//freopen("out.txt", "w+t", stdout);
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%d %d", &p[i].x, &p[i].y);
        sort(p, p+n);
        priority_queue<int, vector<int>, greater<int> > pQ;
        int cnt = 0;
        for(i = 0; i < n; i++) {
            while(!pQ.empty() && pQ.top() <= p[i].x)
                pQ.pop();
            cnt += pQ.size();
            pQ.push(p[i].y);
        }
        printf("Case %d: %d\n", ++cases, cnt);
    }
    return 0;
}
/*
2
0 10
10 20
2
0 10
5 8
2
0 10
5 20
2
0 10
-5 5
2
0 10
0 10
2
0 10
5 10
5
1 5
1 5
3 10
3 10
3 10
*/
