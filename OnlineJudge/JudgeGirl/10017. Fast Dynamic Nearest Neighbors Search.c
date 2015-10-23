#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAXN 262144
#define MAXD 2
#define INF INT_MAX
#define ALPHA 0.75f
#define LOG_ALPHA log2(1.0 / ALPHA)
int KD_TREE_Point_sortIdx = 0, KD_TREE_Point_kD = 2;    
int min(int x, int y) {
	return x < y ? x : y;
}
struct Point {
    int d[MAXD], pid;
};
struct Node {
    struct Node *lson, *rson;
    struct Point pid; 
    int size;
};
struct KD_TREE {

	struct Node nodes[MAXN];
    struct Node *root;
    struct Point data[MAXN], A[MAXN];
    int bufsize, size, kD;
} A, B;
/* Point */
int pt_dist(struct Point *x, struct Point *y) {
	int ret = 0;
	for (int i = 0; i < KD_TREE_Point_kD; i++)
		ret += abs(y->d[i] - x->d[i]);
	return ret;
}
void read(struct Point *x, int id) {
	for (int i = 0; i < KD_TREE_Point_kD; i++)
		scanf("%d", &x->d[i]);
	x->pid = id;
}
/* Node */
struct Node node() {
	struct Node p;
	p.lson = p.rson = NULL, p.size = 1;
	return p;
}
void update(struct Node *x) {
	x->size = 1;
	if (x->lson)	x->size += x->lson->size;
	if (x->rson)	x->size += x->rson->size;
}
int cmp(const void *a, const void *b) {
	struct Point x = *(struct Point *)a;
	struct Point y = *(struct Point *)b;
	int sortIdx = KD_TREE_Point_sortIdx;
	if (x.d[sortIdx] != y.d[sortIdx])
    	return x.d[sortIdx] < y.d[sortIdx] ? -1 : 1;
    return 0;
}
/* KD tree */
void init(struct KD_TREE *tree, int kd) {
	tree->size = tree->bufsize = 0;
	tree->root = NULL;
	KD_TREE_Point_sortIdx = 0;
	KD_TREE_Point_kD = tree->kD = kd;
}
int log2int(int x){
	return __builtin_clz((int)1)-__builtin_clz(x);
}
int isbad(struct Node *u) {
	if (u->lson && u->lson->size > u->size * ALPHA)
		return 1;
	if (u->rson && u->rson->size > u->size * ALPHA)
		return 1;
	return 0;
}    
struct Node* newNode(struct KD_TREE *tree)  {
	struct Node *ret = &(tree->nodes[tree->bufsize++]);
	*ret = node();
	return ret;
}
struct Node* build(struct KD_TREE *tree, int k, int l, int r) {
	if (l > r)	return NULL;
	struct Node *ret = newNode(tree);
	int mid = (l + r)>>1;
	KD_TREE_Point_sortIdx = k;
	qsort(tree->A+l, r-l+1, sizeof(tree->A[0]), cmp);
	ret->pid = tree->A[mid];
	if (l != r) {
		ret->lson = build(tree, (k+1)%tree->kD, l, mid-1);
		ret->rson = build(tree, (k+1)%tree->kD, mid+1, r);
	}
	update(ret);
	return ret;
}
int flatten_size;
void flatten(struct KD_TREE *tree, struct Node *u) {
	if (u == NULL)	return ;
	flatten(tree, u->lson);
	tree->A[flatten_size++] = u->pid;
	flatten(tree, u->rson);
}
int m_insert(struct KD_TREE *tree, struct Node **u, int k, struct Point *x, int dep) {
	if (*u == NULL) {
		(*u) = newNode(tree), (*u)->pid = *x;
		tree->data[tree->size++] = *x;
		return dep <= 0;
	}
	(*u)->size++;
	int t = 0;
	if (x->d[k] < (*u)->pid.d[k])
		t = m_insert(tree, &(*u)->lson, (k+1)%tree->kD, x, dep-1);
	else
		t = m_insert(tree, &(*u)->rson, (k+1)%tree->kD, x, dep-1);
	if (t && !isbad(*u))
		return 1;
	if (t) {
		flatten_size = 0;
		flatten(tree, *u);
		*u = build(tree, k, 0, (*u)->size-1);
	}
	return 0;
}
int heuristic(struct KD_TREE *tree, int h[]) {
	int ret = 0;
	for (int i = 0; i < tree->kD; i++)
		ret += h[i];
	return ret;
}
void closest(struct KD_TREE *tree, struct Node *u, int k, struct Point *x, int h[], int *mndist) {
	if (u == NULL || heuristic(tree, h) >= *mndist)
		return ;
	int dist = pt_dist(&(u->pid), x), old;
	*mndist = min(*mndist, dist), old = h[k];
	if (x->d[k] < u->pid.d[k]) {    		
		closest(tree, u->lson, (k+1)%tree->kD, x, h, mndist);
		h[k] = abs(x->d[k] - u->pid.d[k]);
		closest(tree, u->rson, (k+1)%tree->kD, x, h, mndist);
		h[k] = old;
	} else {
		closest(tree, u->rson, (k+1)%tree->kD, x, h, mndist);
		h[k] = abs(x->d[k] - u->pid.d[k]);
		closest(tree, u->lson, (k+1)%tree->kD, x, h, mndist);
		h[k] = old;
	}
}
void s_insert(struct KD_TREE *tree, struct Point x) {
	m_insert(tree, &tree->root, 0, &x, log2int(tree->size) / LOG_ALPHA);
}
int s_closest(struct KD_TREE *tree, struct Point x) {
	int mndist = INF, h[MAXD] = {};
	closest(tree, tree->root, 0, &x, h, &mndist);
	return mndist;
}
int main() {
	int N;
	struct Point pt;
	while (scanf("%d", &N) == 1) {
		init(&A, 2), init(&B, 2);
		for (int i = 0; i < N; i++) {
			read(&pt, i);
			if (i)	printf("%d\n", s_closest(&B, pt));
			s_insert(&A, pt);
			read(&pt, i);
			printf("%d\n", s_closest(&A, pt));
			s_insert(&B, pt);
		}
	}
	return 0;
}
