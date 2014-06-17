#include <stdio.h>
#include <map>
using namespace std;
struct ELE {
    int probUsed, objItem;
    unsigned long long obj1, obj2;
    ELE(int a, int b, unsigned long long c, unsigned long long d):
        probUsed(a),objItem(b),obj1(c), obj2(d){}
    bool operator<(const ELE &a) const {
        if(obj1 != a.obj1)
            return obj1 < a.obj1;
        if(probUsed != a.probUsed)
            return probUsed < a.probUsed;
        return obj2 < a.obj2;
    }
};
int obj[128], n, m;
map<ELE, int> dp[1<<11];
//map<unsigned long long, int> low2bit;
int low2bit[1008];
int dfs(ELE &node) {
    if(node.objItem <= 1)
        return 0;
    if(dp[node.probUsed].find(node) != dp[node.probUsed].end())
        return dp[node.probUsed][node];
    int &res = dp[node.probUsed][node];
    int i, j, left, right;
    res = 0xffff;
    for(i = 0; i < n; i++) {
        if(!((node.probUsed>>i)&1)) {
            ELE yes(node.probUsed|(1<<i),0,0,0);
            ELE no(node.probUsed|(1<<i),0,0,0);
            unsigned long long x = node.obj1, v;
            while(x) {
                v = x&-x;
                j = low2bit[v%1007];
                if((obj[j]>>i)&1) {
                    yes.objItem++;
                    yes.obj1 |= 1ULL<<j;
                } else {
                    no.objItem++;
                    no.obj1 |= 1ULL<<j;
                }
                x ^= v;
            }
            x = node.obj2;
            while(x) {
                v = x&-x;
                j = low2bit[v%1007];
                if((obj[j+64]>>i)&1) {
                    yes.objItem++;
                    yes.obj2 |= 1ULL<<j;
                } else {
                    no.objItem++;
                    no.obj2 |= 1ULL<<j;
                }
                x ^= v;
            }
            left = dfs(yes);
            if(left+1 >= res)
                continue;
            right = dfs(no);
            res = min(res, max(dfs(yes),dfs(no))+1);
        }
    }
    return res;
}
int main() {
    int i, j;
    char s[20];
    for(i = 0; i < 64; i++) {
        //if(low2bit.find((1ULL<<i)%1007) != low2bit.end())
        //    puts("XX");
        low2bit[(1ULL<<i)%1007] = i;
    }
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0)  break;
        for(i = 0; i < m; i++) {
            scanf("%s", s);
            obj[i] = 0;
            for(j = 0; s[j]; j++) {
                if(s[j] != '0')
                    obj[i] |= 1ULL<<j;
            }
        }
        for(i = (1<<n)-1; i >= 0; i--)
            dp[i].clear();
        ELE node(0,m,0,0);
        for(i = 0; i < m; i++) {
            if(i >= 64)
                node.obj2 |= 1ULL<<(i-64);
            else
                node.obj1 |= 1ULL<<i;
        }
        printf("%d\n", dfs(node));
    }
    return 0;
}
