#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <algorithm>

const int MAXT = (5e+6) + 5;
const int MAXS = ((MAXT)>>5)+5;
struct BitBIT {
    int tree[MAXS], n, m, _sum;
    uint32_t mask[MAXS];
    int prev_zero;
    void init(int n) {
        this->n = n;
        m = (n>>5)+5;
        _sum = 0;
        memset(mask, 0, sizeof(mask[0])*m);
        memset(tree, 0, sizeof(tree[0])*m);
        prev_zero = 0;
    }
    void cast(int x) {
        _sum++;
        mask[(x>>5)+1] |= 1<<(x&31);
        x = (x>>5)+1;
        for (; x < m; x += x&(-x))
            tree[x]++;
    }
    void erase(int x) {
        _sum--;
        mask[(x>>5)+1] ^= 1<<(x&31);
        x = (x>>5)+1;
        for (; x < m; x += x&(-x))
            tree[x]--;
    }
    int prefix(int x) {
        int ret = 0;
        ret = __builtin_popcount(mask[(x>>5)+1]&((x&31) >= 31 ? -1 : (1U<<((x&31)+1))-1));
        x = (x>>5);
        for (; x; x -= x&(-x))
            ret += tree[x];
        return ret;
    }
    int sum() {
        return _sum;
    }
} tree;

static const int MAXN = 32;
static const int MAXM = 1<<24;
static int n, miss[MAXN], allmiss, cache[MAXN];
static int stamp[MAXM], mtime;
static int cached;
void access(int addr) {
    int &st = stamp[addr];
    if (st <= cached) {
        allmiss++;
    } else {
        int cnt = tree.sum() - tree.prefix(st-1);
        if (cnt > cache[n-1]) {
            allmiss++;
            cached = st;
        } else {
            for (int i = 0; i < n && cnt > cache[i]; i++)
                miss[i]++;
        }
        tree.erase(st);
    }
    st = ++mtime;
    tree.cast(st);
}

int main() {
    static char cmd[8];
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            scanf("%d", &cache[i]);
        
        memset(stamp, 0, sizeof(stamp));
        mtime = 0, cached = 0, allmiss = 0;
        tree.init(MAXT);
        
        int addr, b, y, k;
        while (scanf("%s", cmd) == 1 && cmd[0] != 'E') {
            if (cmd[0] == 'A') {
                scanf("%d", &addr);
                access(addr);
            } else if (cmd[0] == 'R') {
                scanf("%d %d %d", &b, &y, &k);
                for (int i = 0; i < k; i++)
                    access(b+y*i);
            } else {
                for (int i = 0; i < n; i++)
                    printf("%d%c", miss[i]+allmiss, " \n"[i==n-1]);
                memset(miss, 0, sizeof(miss[0])*n);
                allmiss = 0;
            }
        }
    }
    return 0;
}
/*
 2
 4 8
 RANGE 1 1 5
 RANGE 2 1 2
 ADDR   99
 STAT
 ADDR   2
 RANGE 5 -1 2
 STAT
 RANGE 0 10000 10
 RANGE 0 20000 5
 RANGE 0 30000 4
 STAT
 END
 */
