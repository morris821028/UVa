#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct Node {
    int key, value;
    int lson, rson, parent;
};
Node D[131072];
void insertCartesianTree(int index, Node D[]) {
    int p = index - 1;
    while(D[p].value > D[index].value)
        p = D[p].parent;
    D[index].lson = D[p].rson;
    D[p].rson = index;
    D[index].parent = p;
}
void preorderMorrisTraversal(int u) {
    int cur = u, prev = 0;
    while (cur) {
        if (D[cur].lson == 0) {
            printf("%d ", D[cur].key);
            cur = D[cur].rson;
        } else {
            prev = D[cur].lson;
            while (D[prev].rson && D[prev].rson != cur)
                prev = D[prev].rson;

            if (D[prev].rson == 0) {
                printf("%d ", D[cur].key);
                D[prev].rson = cur;
                cur = D[cur].lson;
            } else {
                D[prev].rson = 0;
                cur = D[cur].rson;
            }
        }
    }
}
pair<int, int> A[131072];
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout); 
    int N, x;
    while(scanf("%d", &N) == 1 && N) {
        for(int i = 1; i <= N; i++) {
            scanf("%d", &x);
			A[i] = make_pair(x, i);
        }
        sort(A+1, A+1+N);
        D[0].value = -1;
        D[0].lson = D[0].rson = D[0].parent = 0;
        for(int i = 1; i <= N; i++) {
            D[i].lson = D[i].rson = D[i].parent = 0;
            D[i].value = A[i].second, D[i].key = A[i].first;
        }
        for(int i = 1; i <= N; i++) {
            insertCartesianTree(i, D);
        }
        preorderMorrisTraversal(D[0].rson);
        puts("");
    }
    return 0;
}
