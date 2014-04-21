#include <stdio.h> 
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
struct Node {
	int index;
	int val, lson, rson, parent;
};
Node D[500005];
int A[500005];
void insertCartesianTree(int index, Node D[]) {
	int p = index - 1;
	while(D[p].val < D[index].val)
		p = D[p].parent;
	D[index].lson = D[p].rson;
	D[p].rson = index;
	D[index].parent = p;
}
int parent[500005];
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
vector<Qi> query[500005];
int used[500005];
int oput[500000];
void tarjan(int nd) {
	used[nd] = 1;
	for(vector<Qi>::iterator it = query[nd].begin();
        it != query[nd].end(); it++) {
        if(used[it->q]) {
            oput[it->i] = findp(it->q);
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
int main() {
	int N, Q, x, y;
	while(scanf("%d", &N) == 1 && N) {
		for(int i = 1; i <= N; i++)
			scanf(" %d", &A[i]);
		for(int i = N; i >= 0; i--) {
			parent[i] = i;
			query[i].clear();
			used[i] = 0;
		}
		D[0].val = 0x3f3f3f3f;
		D[0].lson = D[0].rson = D[0].parent = 0;
		for(int i = 1; i <= N; i++) {
			D[i].lson = D[i].rson = D[i].parent = 0;
			D[i].val = A[i], D[i].index = i;
		}
		for(int i = 1; i <= N; i++)
			insertCartesianTree(i, D);
		scanf("%d", &Q);
		for(int i = 0; i < Q; i++) {
			scanf("%d %d", &x, &y);
			query[x].push_back(Qi(y, i));
			query[y].push_back(Qi(x, i));
		}
		tarjan(D[0].rson);
		for(int i = 0; i < Q; i++) {
			printf("%d\n", A[oput[i]]);
		}
	}
	return 0;
}
/*
Problem: Find a maximum value for each range interval.

Sample Input:
10 
3 2 4 5 6 8 1 2 9 7
7 
1 5 
3 5
1 10
5 8
6 6 
2 4
2 9 

Sample Output:
6
6
9
8
8
5
9

*/
