#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


const int MAXT = (1e+7) + 5;
struct BIT {
    int tree[MAXT], n, _sum;
    void init(int n) {
        this->n = n;
        _sum = 0;
        memset(tree, 0, sizeof(tree[0])*n);
    }
    void add(int x, int val) {
        _sum += val;
        for (; x < n; x += x&(-x))
            tree[x] += val;
    }
    int query(int x) {
        int ret = 0;
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
        int cnt = tree.sum() - tree.query(st-1);
        if (cnt > cache[n-1]) {
            allmiss++;
            cached = st;
        } else {
            for (int i = 0; i < n && cnt > cache[i]; i++)
                miss[i]++;
        }
        tree.add(st, -1);
    }
    st = ++mtime;
    tree.add(st, 1);
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
