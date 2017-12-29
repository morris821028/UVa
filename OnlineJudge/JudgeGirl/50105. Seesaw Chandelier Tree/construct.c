#include "construct.h"
#include <stdint.h>
#include <stdlib.h>
#define MAXN 32768

static int64_t S[MAXN], M[MAXN];
static Node* build(int l, int r) {    
	if (r < l)
    	return NULL;
    int64_t s = S[r] - S[l-1], m = M[r] - (M[l-1] + (r-l+1)*S[l-1]);
    if (r-l < 2 || s == 0 || m%s) {
    	Node *ret = (Node *) calloc(1, sizeof(Node)), *p;
    	ret->value = S[r]-S[r-1], p = ret;
    	for (int i = r-1; i >= l; i--) {
    		Node *q = (Node *) calloc(1, sizeof(Node));
    		q->value = S[i]-S[i-1];
    		p->left = q;
    		p = q;
		}
        return ret;
    }
    int pos = r-(int) (m/s);
    Node *ret = (Node *) calloc(1, sizeof(Node));
    ret->value = S[pos]-S[pos-1];
    ret->left = build(l, pos-1);
    ret->right = build(pos+1, r);
    return ret;
}
Node* ConstructTree(int A[], int n) {
	for (int i = 1; i <= n; i++) {
		M[i] = M[i-1] + S[i-1];
		S[i] = S[i-1] + A[i-1];
    }
    return build(1, n);
}
