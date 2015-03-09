#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct Node {
    int key, value;
    int lson, rson, parent;
};
Node D[65536];
void insertCartesianTree(int index, Node D[]) {
    int p = index - 1;
    while(D[p].value > D[index].value)
        p = D[p].parent;
    D[index].lson = D[p].rson;
    D[p].rson = index;
    D[index].parent = p;
}
void dfsPrint(int node) {
    if(node == 0)    return;
    printf("%d ", D[node].key);
    dfsPrint(D[node].lson);
    dfsPrint(D[node].rson);
}
int main() {
    int N, x;
    pair<int, int> A[65536];
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
        dfsPrint(D[0].rson);
        puts("");
    }
    return 0;
}
