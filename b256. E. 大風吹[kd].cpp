#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct Node {
    Node *l, *r;
    int idx;
};
Node buf[50005];
int bufsize;
int pt[50005][5];
int L[5];
int N, K, M;
int A[50005];
int sortIdx;
bool cmp(int a, int b) {
    return pt[a][sortIdx] < pt[b][sortIdx];
}
Node* kdTreebuild(int k, int l, int r) {
    if(l > r)
        return NULL;
    sortIdx = k;
    sort(A+l, A+r+1, cmp);
    int m = (l + r)/2;
    Node *ret = &buf[bufsize++];
    ret->idx = A[m]; // point index
    if(l != r) {
        ret->l = kdTreebuild((k+1)%K, l, m-1);
        ret->r = kdTreebuild((k+1)%K, m+1, r);
    } else {
        ret->l = ret->r = NULL;
    }
    return ret;
}
int max_dist = 0x3f3f3f3f, banIdx;
int dist(int idx) {
	if(banIdx == idx)
		return 0x3f3f3f3f;
    int ret = 0;
    for(int i = 0; i < K; i++)
        ret += (pt[idx][i] - L[i]) * (pt[idx][i] - L[i]);
    return ret;
}
int h_function(int h[]) {
    int ret = 0;
    for(int i = 0; i < K; i++)
        ret += h[i];
    return ret;
}
struct pQcmp {
    bool operator() (int a, int b) {
    	int d1 = dist(a);
    	int d2 = dist(b);
    	if(d1 != d2)
    		return d1 < d2;
    	return a < b;
    }
};
priority_queue<int, vector<int>, pQcmp> pQ;
void DC(Node *nd, int k, int h[]) {
    if(nd == NULL || h_function(h) >= max_dist)
        return;
    int d = dist(nd->idx);
    if(d < max_dist) {
        pQ.push(nd->idx);
        if(pQ.size() == M+1) {
            max_dist = dist(pQ.top());
            pQ.pop();
        }
    }
    int hk = h[k];
    if(L[k] < pt[nd->idx][k]) {
        if(nd->l != NULL)
            DC(nd->l, (k+1)%K, h);    
        if(nd->r != NULL) {
            h[k] = (pt[nd->idx][k] - L[k])*(pt[nd->idx][k] - L[k]);
            DC(nd->r, (k+1)%K, h);
            h[k] = hk;
        }
    } else {
        if(nd->l != NULL) {
            h[k] = (pt[nd->idx][k] - L[k])*(pt[nd->idx][k] - L[k]);
            DC(nd->l, (k+1)%K, h);
            h[k] = hk;
        }
        if(nd->r != NULL)
            DC(nd->r, (k+1)%K, h);
    }
}
int main() {
	K = 2;
	scanf("%*d");
    while(scanf("%d", &N) == 1) {
    	int i, j, k;
        for(i = 0; i < N; i++) {
            for(j = 0; j < K; j++)
                scanf("%d", &pt[i][j]);
            A[i] = i;
        }
        bufsize = 0;
        Node *root = kdTreebuild(0, 0, N-1);
        int cutCond[50005];
        for(i = 0; i < N; i++)
        	cutCond[i] = 0x3f3f3f3f;
        for(i = 0; i < N; i++) {
        	M = 1;
            max_dist = cutCond[i];
            banIdx = i;
            for(j = 0; j < K; j++)
            	L[j] = pt[i][j];
            int h[5] = {};
            DC(root, 0, h);
            int best = pQ.top();
            pQ.pop();
            cutCond[best] = min(cutCond[best], max_dist + 1);
            printf("%d\n", best + 1);
        }
    }
    return 0;
}
