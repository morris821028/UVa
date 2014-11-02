#include <cstdio>
const int V = 40010;
const int E = V*200*2;
const int INF = 1<<29;
typedef struct Edge{
    int v, cap, flow;
    Edge *next, *re;
}Edge;
class MaxFlow{
    public:
    Edge edge[E], *adj[V], *pre[V], *arc[V];
    int e, n, d[V], q[V], numb[V];
    void Init(int x){
        n = x;
        for (int i = 0; i < n; ++i) adj[i] = NULL;
        e = 0;
    }
    void Addedge(int x, int y, int flow){
        edge[e].v = y, edge[e].cap = flow, edge[e].next = adj[x];
        edge[e].re = &edge[e+1]; adj[x] = &edge[e++];
        edge[e].v = x, edge[e].cap = 0, edge[e].next = adj[y];
        edge[e].re = &edge[e-1]; adj[y] = &edge[e++];
    }
    void Bfs(int v){
        int front = 0, rear = 0, r = 0, dis = 0;
        for (int i = 0; i < n; ++i) d[i] = n, numb[i] = 0;
        d[v] = 0;++numb[0];
        q[rear++] = v;
        while (front != rear){
            if (front == r) ++dis, r = rear;
            v = q[front++];
            for (Edge *i = adj[v]; i != NULL; i = i->next){
                int t = i->v;
                if (d[t] == n) d[t] = dis, q[rear++] = t, ++numb[dis];
            }
        }
    }
    int Maxflow(int s, int t){
        int ret = 0, i, j;
        Bfs(t);
        for (i = 0; i < n; ++i) pre[i] = NULL, arc[i] = adj[i];
        for (i = 0; i < e; ++i) edge[i].flow = edge[i].cap;
        i = s;
        while (d[s] < n){
            while (arc[i] && (d[i] != d[arc[i]->v]+1 || !arc[i]->flow)) arc[i] = arc[i]->next;
            if (arc[i]){
                j = arc[i]->v;
                pre[j] = arc[i];
                i = j;
                if (i == t){
                    int update = INF;
                    for (Edge *p = pre[t]; p != NULL; p = pre[p->re->v])
                        if (update > p->flow) update = p->flow;
                    ret += update;
                    for (Edge *p = pre[t]; p != NULL; p = pre[p->re->v])
                        p->flow -= update, p->re->flow += update;
                    i = s;
                }
            }
            else{
                int min = n-1;
                for (Edge *p = adj[i]; p != NULL; p = p->next)
                    if (p->flow && min > d[p->v]) min = d[p->v];
                if (--numb[d[i]] == 0) return ret;
                d[i] = min+1;
                ++numb[d[i]];
                arc[i] = adj[i];
                if (i != s) i = pre[i]->re->v;
            }
        }
        return ret;
    }
};

MaxFlow g;

int prime[10000];
int tot = 0;
bool used[10000];

const int MAX = 500010;

int in[MAX];
int cnt[MAX];
int arr[V];

void Init(){
    int x = 7200;
//    printf("%d\n", x*x);
    for (int i = 2; i < x; ++i)
        if (!used[i]){
//            printf("%d\n", i);
            prime[tot++] = i;
            cnt[i] = 1;
            for (int j = i*i; j < x; j += i) used[j] = 1;
        }
//    printf("prime[%d] = %d\n", tot-1, prime[tot-1]*prime[tot-1]);
//    printf("%d\n", tot);
    for (int i = 2; i < MAX; ++i){
        for (int j = 0; j < tot && prime[j] <= i; ++j)
            if (i%prime[j] == 0){
                cnt[i] = cnt[i/prime[j]]+1;
                break;
            }
        if (!cnt[i]) cnt[i] = 1;
    }
    for (int i = 1; i <= 100; ++i) printf("%d %d\n", i, cnt[i]);
//    puts("Yes!");
}

int main()
{
    Init();
    int t, n, cas = 0;
    scanf("%d", &t);
    while (t--){
        scanf("%d", &n);
        for (int i = 0; i < MAX; ++i) in[i] = -1;
        for (int i = 0; i < n; ++i){
            scanf("%d", &arr[i]);
            in[arr[i]] = i;
        }
        g.Init(n+2);
        int S = n, T = n+1;
        for (int i = 0; i < n; ++i){
            int x = arr[i];
            if (cnt[x]&1) g.Addedge(S, i, 1);
            else g.Addedge(i, T, 1);
//            else{
//                printf("Not Prime %d\n", x);
                for (int j = 0; j < tot && prime[j] <= x; ++j){
                    if (x%prime[j]) continue;
//                    printf("x = %d factor = %d\n", x, prime[j]);
                    int y = x/prime[j];
                    if (in[y] != -1){
                        int v = in[y];
                        if (cnt[x]&1) g.Addedge(i, v, 1);
                        else g.Addedge(v, i, 1);
                    }
                    if (y > prime[tot-1] && cnt[y] == 1){
                        y = prime[j];
                        if (in[y] != -1){
                            int v = in[y];
                            if (cnt[x]&1) g.Addedge(i, v, 1);
                            else g.Addedge(v, i, 1);
                        }
                    }
                }
//            }
//            if (!flag && in[1] != -1) g.Addedge(i, in[1], 1);
        }
        printf("Case %d: %d\n", ++cas, n-g.Maxflow(S, T));
    }
    return 0;
}
