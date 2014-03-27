#include <stdio.h> 
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
struct Node {
	int index;
	int val, lson, rson, parent;
};
Node D[100005];
int A[100005], B[100005];
void insertCartesianTree(int index, Node D[]) {
	int p = index - 1;
	while(D[p].val < D[index].val)
		p = D[p].parent;
	D[index].lson = D[p].rson;
	D[p].rson = index;
	D[index].parent = p;
}
int parent[100005];
int findp(int x) {
    return parent[x] == x ? x : parent[x]=findp(parent[x]);
}
void joint(int x, int y) {
    x = findp(x), y = findp(y);
    parent[x] = y;
}
struct Qi {
    int q, i;
    Qi(int a = 0, int b = 0):q(a), i(b) {
    }
};
vector<Qi> query[100005];
int used[100005];
int oput[100000];
void tarjan(int nd) {
	used[nd] = 1;
	for(vector<Qi>::iterator it = query[nd].begin();
        it != query[nd].end(); it++) {
        if(used[it->q]) {
            oput[it->i] = max(B[findp(it->q)], oput[it->i]);
        }
    }
    int u;
    if(u = D[nd].lson) {
    	tarjan(u), joint(u, nd);
    }
    if(u = D[nd].rson) {
    	tarjan(u), joint(u, nd);
    }
}

int leftmost[100005], rightmost[100005];
void build(int A[], int N, int B[]) {
	int before = A[1], cnt = 0;
	for(int i = 1; i <= N; i++) {
		if(A[i] == before)
			cnt++;
		else
			cnt = 1;
		B[i] = cnt, before = A[i];
	}
	leftmost[1] = 1, rightmost[N] = N;
	for(int i = 2; i <= N; i++) {
		leftmost[i] = A[i] == A[i-1] ? leftmost[i-1] : i;
	}
	for(int i = N-1; i >= 1; i--) {
		rightmost[i] = A[i] == A[i+1] ? rightmost[i+1] : i;
	}
}
int main() {
	int N, Q, x, y;
	while(scanf("%d %d", &N, &Q) == 2 && N) {
		for(int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
		build(A, N, B);
		for(int i = N; i >= 0; i--) {
			parent[i] = i;
			query[i].clear();
			used[i] = 0;
		}
		D[0].val = 0x3f3f3f3f;
		D[0].lson = D[0].rson = D[0].parent = 0;
		for(int i = 1; i <= N; i++) {
			D[i].lson = D[i].rson = D[i].parent = 0;
			D[i].val = B[i], D[i].index = i;
		}
		for(int i = 1; i <= N; i++)
			insertCartesianTree(i, D);
		for(int i = 0; i < Q; i++) {
			scanf("%d %d", &x, &y);
			int ni, nj;
			ni = rightmost[x] + 1;
			nj = leftmost[y] - 1;
			oput[i] = 0;
			if(ni <= nj) {
				query[ni].push_back(Qi(nj, i));
				query[nj].push_back(Qi(ni, i));
				oput[i] = max(ni - x, y - nj);
			} else {
				if(A[x] != A[y])
					oput[i] = max(ni - x, y - nj);
				else
					oput[i] = y - x + 1;
			}
		}
		tarjan(D[0].rson);
		for(int i = 0; i < Q; i++) {
			printf("%d\n", oput[i]);
		}
	}
	return 0;
}
/*
Sample Input:
10 3
-1 -1 1 1 1 1 3 10 10 10
2 3
1 10
5 10

Sample Output:
1
4
3

*/
