#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 131072;
const int MAXM = 131072;
const int MAXD = 2;
const int INF = INT_MAX;
const double ALPHA = 0.75;
const double LOG_ALPHA = log2(1.0 / ALPHA);
class KD_TREE {
public:
    struct Point {
    	static int kD;
        int d[MAXD], pid;
        int dist(Point &x) {
        	int ret = 0;
        	for (int i = 0; i < kD; i++)
        		ret += abs(d[i] - x.d[i]);
        	return ret;
        }
        void read(int id = 0) {
        	for (int i = 0; i < kD; i++)
        		scanf("%d", &d[i]);
        	pid = id;
        }    	
        static int sortIdx;
        bool operator<(const Point &x) const {
            return d[sortIdx] < x.d[sortIdx];
        }
        int compare(const Point &x) {
        	for (int i = 0; i < 2; i++) {
        		if (d[i] != x.d[i])
        			return d[i] < x.d[i] ? -1 : 1;
			}
			return 0;
		}
    };
    struct Node {
        Node *lson, *rson, *p;
        Point pid; 
        int size, vsz, has;
        Node() {
        	lson = rson = NULL;
        	size = 1, vsz = 1, has = 1;
        }
        void update() {
        	size = 1, vsz = 1;
        	if (lson)	size += lson->size, vsz += lson->vsz;
        	if (rson)	size += rson->size, vsz += rson->vsz;
        }
    } nodes[MAXN];
    Node *root;
    Node *closest_nd;
    Point A[MAXM], closest_pt;
    int bufsize, size, kD;
    void init(int kd) {
    	size = bufsize = 0;
    	root = NULL;
    	Point::sortIdx = 0;
        Point::kD = kD = kd;
    }
    void insert(Point x) {
    	insert(root, 0, x, log2int(size) / LOG_ALPHA);
    }
    int closest(Point x) {
    	int mndist = INF, h[MAXD] = {};
    	closest(root, 0, x, h, mndist);
    	return mndist;
    }
    int log2int(int x) {
    	int i;
    	for (i = 0; (1<<i) < x; i++)
    	return i;
//        return __builtin_clz((int)1)-__builtin_clz(x);
    }
    inline int isbad(Node *u) {
    	if (u->lson && u->lson->size > u->size * ALPHA)
    		return 1;
    	if (u->rson && u->rson->size > u->size * ALPHA)
    		return 1;
    	return 0;
    }    
    Node* newNode()  {
    	Node *ret = &nodes[bufsize++];
    	*ret = Node();
    	return ret;
    }
    Node* build(Node *p, int k, int l, int r) {
    	if (l > r)	return NULL;
    	if (k == kD)	k = 0;
    	Node *ret = newNode();
    	int mid = (l + r)>>1;
    	Point::sortIdx = k;
    	sort(A+l, A+r+1);
    	ret->pid = A[mid];
        ret->lson = build(ret, k+1, l, mid-1);
        ret->rson = build(ret, k+1, mid+1, r);
    	ret->update(), ret->p = p;
    	return ret;
    }
    void flatten(Node *u, Point* &buf) {
    	if (u == NULL)	return ;
    	flatten(u->lson, buf);
    	*buf = u->pid, buf++;
    	flatten(u->rson, buf);
    }
    bool insert(Node* &u, int k, Point &x, int dep) {
    	if (u == NULL) {
    		u = newNode(), u->pid = x;
    		return dep <= 0;
    	}
    	u->size++;
    	int t = 0;
    	if (x.d[k] <= u->pid.d[k])
    		t = insert(u->lson, (k+1)%kD, x, dep-1);
    	else
    		t = insert(u->rson, (k+1)%kD, x, dep-1);
    	if (t && !isbad(u))
    		return 1;
    	if (t) {
    		Point *ptr = &A[0];
    		Node *up = u->p;
    		flatten(u, ptr);
    		u = build(NULL, k, 0, u->size-1);
    		u->p = up;
    	}
    	return 0;
    }
    int heuristic(int h[]) {
    	int ret = 0;
    	for (int i = 0; i < kD; i++)
    		ret += h[i];
    	return ret;
    }
    void reduce() {
    	Node *u = closest_nd;
    	u->has = 0;
    	while (u) {
    		u->vsz--;
    		u = u->p;
		}
	}
    void closest(Node *u, int k, Point &x, int h[], int &mndist) {
    	if (u == NULL || heuristic(h) > mndist)
    		return ;
    	if (u->vsz == 0)
    		return ;
    	int dist = u->pid.dist(x), old;
    	if (u->has == 1) {
    		if (dist < mndist || (dist == mndist && closest_pt.compare(u->pid) > 0))
    			closest_pt = u->pid, closest_nd = u;
    		mndist = min(mndist, dist);
    	}
    	old = h[k];
    	if (x.d[k] <= u->pid.d[k]) {    		
            closest(u->lson, (k+1)%kD, x, h, mndist);
            h[k] = abs(x.d[k] - u->pid.d[k]);
            closest(u->rson, (k+1)%kD, x, h, mndist);
            h[k] = old;
    	} else {
    		closest(u->rson, (k+1)%kD, x, h, mndist);
            h[k] = abs(x.d[k] - u->pid.d[k]);
            closest(u->lson, (k+1)%kD, x, h, mndist);
            h[k] = old;
    	}
    }
} A;
int KD_TREE::Point::sortIdx = 0, KD_TREE::Point::kD = 2;

int main() {
    int N, H, W;
    KD_TREE::Point pt[131072], st;
    while (scanf("%d %d", &H, &W) == 2) {
    	st.read();
    	scanf("%d", &N);
        A.init(2);
        for (int i = 0; i < N; i++)
        	A.A[i].read();
        A.root = A.build(NULL, 0, 0, N-1);
        
    	long long ret = 0;
        for (int i = 0; i < N; i++) {
        	A.closest(st);
        	A.reduce();
        	ret += abs(A.closest_pt.d[0] - st.d[0])+abs(A.closest_pt.d[1] - st.d[1]);
        	st = A.closest_pt;
		}
		printf("%lld\n", ret);
    }
    return 0;
}
