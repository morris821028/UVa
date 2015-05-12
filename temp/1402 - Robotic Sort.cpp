#include <stdio.h>
#include <math.h>
#include <stack>
#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
// Unrolled Linked List
const int MAXPILE = 512;
const int MAXN = 131072;
class UnrolledLinkedList{
public:
	struct Node {
		int v[MAXPILE], vn;
		int rev_label, pid;
		Node *next;
		Node() {
			vn = rev_label = 0;
			next = NULL;
		}
		void relax() {
			if (rev_label) {
				for(int i = 0, j = vn-1; i < j; i++, j--)
        			swap(v[i], v[j]);
        		rev_label = 0;
        	}
		}
	};
	Node *head;
	int PSIZE, pid;
	int e_pos[MAXN], e_id[MAXN];
	void init() {
		free();
		head = NULL, PSIZE = MAXPILE /2;
		pid = 0;
	}
	Node* getNode() {
		Node* p = new Node();
		p->pid = pid++;
		return p;
	}
	void remap(Node *u) {
		for (int i = 0; i < u->vn; i++) 
			e_pos[u->v[i]] = i, e_id[u->v[i]] = u->pid;
	}
	int find(int e_val) {
		int pid = e_id[e_val];
		int sum_element = 0;
		Node *u, *v;
		
		for (u = head; u != NULL && u->pid != pid; u = u->next)
			sum_element += u->vn;
			
//		printf("find %d - %d\n", e_val, pid);
		assert(u != NULL);
		if (u->rev_label)
			return sum_element + u->vn - 1 - e_pos[e_val];
		else
			return sum_element + e_pos[e_val];
	}
	void set(int A[], int n) {
		init();
		Node *u, *v;
		
		head = getNode();
		u = head, v = NULL;
		PSIZE = min(PSIZE, (int) sqrt(n));
		for (int i = 0; i < n; i++) {
			if (u->vn == PSIZE) {
				u->next = getNode();
				v = u, u = u->next;
			}
			u->v[u->vn++] = A[i];
		}
		for (u = head; u != NULL; u = u->next)
			remap(u);
	}
	void shrinkList() {
	    Node *u, *v;
	    u = head;
	    for (u = head; u != NULL && u->next != NULL; u = u->next) {
	        if (u->vn + u->next->vn <= 2 * PSIZE) { // merge
	            v = u->next;
	            u->relax(), v->relax();
	            for (int i = u->vn, j = 0; j < v->vn; i++, j++)
	                u->v[i] = v->v[j];
	            u->vn += v->vn;
				remap(u);
				u->next = v->next;
	            delete v;
	        }
	    }
	}
	void splitNode(Node *u, int left_size) { // length(left) = v
	    Node *v = getNode();
		u->relax();
	    v->next = u->next;
	    u->next = v;
	    v->vn = u->vn - left_size;
	    for(int i = left_size, j = 0; i < u->vn; i++, j++)
	        v->v[j] = u->v[i];
	    u->vn = left_size;
	    remap(u), remap(v);
	}
	void reverse(int l, int r) { // [l, r] = [0, n-1]
		Node *lptr, *rptr, *u, *v;
    	Node *lpre, *rpre, *rnext;
    	int sum_element = 0;
    	
    	u = head, v = NULL;
    	for (u = head, v = NULL; u != NULL; v = u, u = u->next) {
    		if (sum_element < l && l < sum_element + u->vn) 
            	splitNode(u, l - sum_element); // left[...l-1], right[l...]
        	if (sum_element <= r && r < sum_element + u->vn)
            	splitNode(u, r - sum_element + 1);
            	
            if (sum_element == l)
        		lptr = u, lpre = v;
			if (sum_element + u->vn - 1 == r)
        		rptr = u, rpre = v;
        	
        	sum_element += u->vn;
    	}
    	    	
//    	debug();
    	
    	rnext = rptr->next;
    	stack<Node*> stk;
    	for (u = lptr; u != rnext; u = u->next) {
    		u->rev_label = !u->rev_label;
    		stk.push(u);
    	}
    	
    	if (lpre == NULL) {
    		head = stk.top();
        	u = head, stk.pop();
        	while (!stk.empty()) {
            	u->next = stk.top(), stk.pop();
            	u = u->next;
        	}
        	u->next = rnext;
    	} else {
    		u = lpre;
    		while (!stk.empty()) {
    			u->next = stk.top(), stk.pop();
            	u = u->next;
        	}
        	u->next = rnext;
    	}
    	
    	shrinkList();
	}
	void debug() {
		Node *u = head;
    	while (u != NULL) {
        	printf("%d : %d, ", u->pid, u->rev_label);
        	for(int i = 0; i < u->vn; i++)
            	printf("%d ", u->v[i]);
        	puts("");
        	u = u->next;
    	}
    	puts("====");
	}
	void free() {
		Node *u = head, *v = NULL;
    	while(u != NULL) {
        	v = u, u = u->next;
        	delete v;
    	}
	}
} g;

int A[MAXN];
int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		vector< pair<int, int> > B;
		for (int i = 0; i < n; i++) {
			scanf("%d", &A[i]);
			B.push_back(make_pair(A[i], i));
		}
		
		sort(B.begin(), B.end());
		
		map< pair<int, int>, int > C;
		for (int i = 0; i < B.size(); i++)
			C[B[i]] = i;
		
		for (int i = 0; i < n; i++)
			A[i] = C[make_pair(A[i], i)];
		
		g.set(A, n);
//		g.debug();
		
		vector<int> ret;
		for (int i = 0; i < n; i++) {
			int pos = g.find(i);
			g.reverse(i, pos);
			ret.push_back(pos);
//			g.debug();
		}
		
		for (int i = 0; i < n; i++)
			printf("%d%c", ret[i] + 1, i == n-1 ? '\n' : ' ');
		
	}
	return 0;
}
/*
6 
3 4 5 1 6 2 
4 
3 3 2 1 
0

10
5 18 19 12 7 12 0 2 11 9
1
4
19
5 17 8 10 13 18 10 5 3 15 2 19 12 10 2 14 18 0 6
12
15 13 7 14 15 7 12 15 4 10 6 3
15
18 7 5 6 5 5 10 9 2 4 9 10 7 13 19
5
3 4 1 1 3
6
8 0 6 2 6 16
7
17 5 12 1 3 9 13
1
8
10
15 19 17 19 17 18 2 12 0 10
10
5 1 14 6 7 12 15 17 5 11
0
*/
