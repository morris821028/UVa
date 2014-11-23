#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 8192
#define MAXD 8
#define INF 0x3f3f3f3f
class rangeTree {
	public:	
	struct PointD {
		int d[MAXD];
		int label, w;
	};
	struct Node {
		
	};
	class segTree {
		public:
		vector <PointD> data;
		vector <segTree> tree;
		vector < pair<int, int> > nodes;
		vector <int> A;
		int K;
		void store(PointD &p) {
			data.push_back(p);
		}
		void prepare(int K, int fK) {
			this->K = K;
			vector<int> val;
			vector<int>::iterator it;
			for (int i = 0; i < data.size(); i++)
				val.push_back(data[i].d[K]);
			sort(val.begin(), val.end());
  			it = std::unique(val.begin(), val.end());
  			val.resize(std::distance(val.begin(), it));
  			A = val;
  			tree.resize((binary_upper(val.size()) << 1) + 5);
  			for (int i = 0; i < tree.size(); i++)
  				tree[i].K = K + 1;
  			if (K + 1 == fK)
  				nodes.resize((binary_upper(val.size()) << 1) + 5);
  			for (int i = 0; i < data.size(); i++)
  				insert(1, 0, A.size() - 1, data[i].d[K], data[i]);
  			data.clear();
  			if (K + 1 < fK) {
  				for (int i = 0; i < tree.size(); i++)
  					tree[i].prepare(K + 1, fK);
  			}
		}
		void merge(segTree &l, segTree &r) {
			
		}
		void insert(int k, int l, int r, int x, PointD &p) {
			if (l == r) {
				tree[k].store(p);
				if (nodes.size())
					nodes[k].first += p.w, nodes[k].second++;
				return ;
			}
			if (l > r)	return;
			int m = (l + r) / 2;
			if (x <= A[m])
				insert(k<<1, l, m, x, p);
			else
				insert(k<<1|1, m+1, r, x, p);
			tree[k].merge(tree[k<<1], tree[k<<1|1]);
			if (nodes.size())
				nodes[k].first += p.w, nodes[k].second++;
		}
		int binary_upper(int n) {
			int m = 1;
			for (m = 1; m < n; m <<= 1);
			return m;
		}
		pair<int, int> query(int k, int l, int r, int L[], int R[], int fK) {
			pair<int, int> ret, tmp;
			if (A.size() == 0 || R[K] < A[l] || A[r] < L[K])	
				return make_pair(0, 0);
//			printf("[%d] %d %d %d\n", K, k, A[l], A[r]);
			if (L[K] <= A[l] && A[r] <= R[K]) {
				if (K == fK - 1) {
//					printf("%d %d\n", nodes[k].first, nodes[k].second);
					return nodes[k];
				}
				ret = tree[k].query(1, 0, tree[k].A.size() - 1, L, R, fK);
				return ret;
			}
			int m = (l + r) / 2;
			if (L[K] <= A[m]) {
				tmp = query(k<<1, l, m, L, R, fK);
				ret.first += tmp.first, ret.second += tmp.second;
			} 
			if (R[K] > A[m]) {
				tmp = query(k<<1|1, m+1, r, L, R, fK);
				ret.first += tmp.first, ret.second += tmp.second;
			}
			return ret;
		}
	};
	PointD pt[MAXN];
	segTree tree;
	int K;
	void prepare(int n) {
		tree = segTree();
		for (int i = 0; i < n; i++)
			tree.store(pt[i]);
		tree.prepare(0, K);
	}
	pair<int, int> query(int L[], int R[]) {
		tree.query(1, 0, tree.A.size() - 1, L, R, K);
	}
};

rangeTree tree;
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n, m, q, x;
	int cases = 0;
	int L[MAXD], R[MAXD];
    while (scanf("%d %d", &n, &m) == 2) {
    	tree.K = m;
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < m; j++)
    			scanf("%d", &tree.pt[i].d[j]);
    		scanf("%d", &tree.pt[i].w);
    		tree.pt[i].label = i;
    	}
    	tree.prepare(n);
    	scanf("%d", &q);
    	while (q--) {
    		for (int i = 0; i < m; i++)
    			scanf("%d", &L[i]);
    		for (int i = 0; i < m; i++)
    			scanf("%d", &R[i]);
    		pair<int, int> ret = tree.query(L, R);
    		printf("Case %d: %d %d\n", ++cases, ret.first, ret.second);
    	}
    }
    return 0;
}
/*
6 2
1 3 1
2 5 2
3 1 4
4 2 8
5 4 16
6 1 32
5
0 0
4 4
0 0
6 6
4 1
6 4
3 1
6 1
1 2
3 4
*/ 
