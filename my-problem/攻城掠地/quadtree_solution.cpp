#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
class QuadTree {
public:
	struct Node {
	    int sum, son[4];
	    Node() {
	    	sum = 0;
	    	memset(son, 0, sizeof(son));
	    }
	} tree[MAXN<<1];
	int nodesize;
	vector< pair<int, int> > Q;
	void build(int k, int lx, int rx, int ly, int ry) {
	    tree[k] = Node();
	    tree[k].sum = (rx-lx+1) * (ry-ly+1);
	    if (lx == rx && ly == ry)
	        return;
	    int mx = (lx+rx)>>1, my = (ly+ry)>>1;
	    if (lx <= mx) {
	        if (ly <= my) {
	            tree[k].son[0] = ++nodesize;
	            build(nodesize, lx, mx, ly, my);
	        }
	        if (ry > my) {
	            tree[k].son[1] = ++nodesize;
	            build(nodesize, lx, mx, my+1, ry);
	        }
	    }
	    if (rx > mx) {
	        if (ly <= my) {
	            tree[k].son[2] = ++nodesize;
	            build(nodesize, mx+1, rx, ly, my);
	        }
	        if (ry > my) {
	            tree[k].son[3] = ++nodesize;
	            build(nodesize, mx+1, rx, my+1, ry);
	        }
	    }
	}
	void pushup(int k) {
		int ret = 0;
		for (int i = 0; i < 4; i++)
			if (tree[k].son[i])
				ret += tree[tree[k].son[i]].sum;
		tree[k].sum = ret;
	}
	void fetch(int k, int lx, int rx, int ly, int ry, int a, int b, int c, int d) {
		if (tree[k].sum == 0)
			return ;
		if (lx == rx && ly == ry) {
			Q.push_back(make_pair(lx, ly));
			tree[k].sum--;
			return ;
		}
		int mx = (lx+rx)>>1, my = (ly+ry)>>1; 
	    if (a <= mx) {
	        if (c <= my) {
	            if (tree[k].son[0] && tree[tree[k].son[0]].sum)
	                fetch(tree[k].son[0], lx, mx, ly, my, a, b, c, d);
	        }
	        if (d > my) {
	            if (tree[k].son[1] && tree[tree[k].son[1]].sum)
	                fetch(tree[k].son[1], lx, mx, my+1, ry, a, b, c, d);
	        }
	    }
	    if (b > mx) {
	        if (c <= my) {
	            if (tree[k].son[2] && tree[tree[k].son[2]].sum)
	                fetch(tree[k].son[2], mx+1, rx, ly, my, a, b, c, d);
	        }
	        if (d > my) {
	            if (tree[k].son[3] && tree[tree[k].son[3]].sum)
	                fetch(tree[k].son[3], mx+1, rx, my+1, ry, a, b, c, d);
	        }
	    }
	    pushup(k);
	}
	void init(int R, int C) {
		nodesize = 1;
		build(1, 1, R, 1, C);
	}
} tree;
int main() {
	int R, C, Q;
	int lx, ly, rx, ry;
	while (scanf("%d %d", &R, &C) == 2) {
		tree.init(R, C);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
			tree.Q.clear();
			tree.fetch(1, 1, R, 1, C, lx, rx, ly, ry);
			sort(tree.Q.begin(), tree.Q.end());
			printf("%d", (int) tree.Q.size());
			for (auto &e : tree.Q)
				printf(" (%d, %d)", e.first, e.second);
			puts("");
		}
	}
	return 0;
}
