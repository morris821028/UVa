#include <bits/stdc++.h>
using namespace std;
const int MAXN = 131072;
const int MAXM = 50005;
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
    };
    struct Node {
        Node *lson, *rson;
        Point pid; 
        int size;
        Node() {
        	lson = rson = NULL;
        	size = 1;
        }
        void update() {
        	size = 1;
        	if (lson)	size += lson->size;
        	if (rson)	size += rson->size;
        }
    } nodes[MAXN];
    Node *root;
    Point A[MAXM];
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
private:
	int log2int(int x){
		return __builtin_clz((int)1)-__builtin_clz(x);
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
    Node* build(int k, int l, int r) {
    	if (l > r)	return NULL;
    	if (k == kD)	k = 0;
    	Node *ret = newNode();
    	int mid = (l + r)>>1;
    	Point::sortIdx = k;
    	sort(A+l, A+r+1);
    	ret->pid = A[mid];
		ret->lson = build(k+1, l, mid-1);
		ret->rson = build(k+1, mid+1, r);
    	ret->update();
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
    		flatten(u, ptr);
    		u = build(k, 0, u->size-1);
    	}
    	return 0;
    }
    int heuristic(int h[]) {
    	int ret = 0;
    	for (int i = 0; i < kD; i++)
    		ret += h[i];
    	return ret;
    }
    void closest(Node *u, int k, Point &x, int h[], int &mndist) {
    	if (u == NULL || heuristic(h) >= mndist)
    		return ;
    	int dist = u->pid.dist(x), old;
    	mndist = min(mndist, dist), old = h[k];
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
} A, B;
int KD_TREE::Point::sortIdx = 0, KD_TREE::Point::kD = 2;

int main() {
	int N;
	KD_TREE::Point pt;
	while (scanf("%d", &N) == 1) {
		A.init(2), B.init(2);
		for (int i = 0; i < N; i++) {
			pt.read(i);
			if (i)	printf("%d\n", B.closest(pt));
			A.insert(pt);
			pt.read(i);
			printf("%d\n", A.closest(pt));
			B.insert(pt);
		}
	}
	return 0;
}

