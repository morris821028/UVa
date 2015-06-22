#include <stdio.h>
#include <math.h>
#include <stack>
#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 32767;
const int MAXQ = 131072;
class UnrolledLinkedList {
public:
	struct Node {
		vector<int> A, B;
		Node *next, *alias;
		Node() {
			A.clear(), B.clear(), next = alias = NULL;
		}
		Node* real() {
			if (alias)	return alias;
			return this;
		}
		void insert(int x, int val) {
			if (alias) {
				A = alias->A;
				relax(), alias = NULL;
			}
			A.insert(A.begin() + x, val);
			B.resize(A.size());
			B[A.size()-1] = val;
			for (int i = (int) A.size()-1; i > 0 && B[i] < B[i-1]; i--)
				swap(B[i], B[i-1]);
		}
		void erase(int x) {
			assert(x >= 0 && x < A.size());
			int val = A[x];
			A.erase(A.begin()+x);
			B.erase(lower_bound(B.begin(), B.end(), val));
		}
		void change(int x, int val) {
			assert(x >= 0 && x < A.size());
			int t = A[x];
			A[x] = val;
			B.erase(lower_bound(B.begin(), B.end(), t));
			B.resize(A.size());
			B[A.size()-1] = val;
			for (int i = (int) A.size()-1; i > 0 && B[i] < B[i-1]; i--)
				swap(B[i], B[i-1]);
		}
		void relax() {
			B = A;
			sort(B.begin(), B.end());
		}
	};
	int MAXPILE, PSIZE;
	Node* init(int A[], int n) { // A[1:n]
		PSIZE = max((int) sqrt(n), 2);
		MAXPILE = PSIZE<<1;
		
		Node *u, *v, *head;
		
		head = newNode();
		u = head, v = NULL;
		for (int i = 1; i <= n; i++) {
			if (u->A.size() == PSIZE) {
				u->next = newNode();
				v = u, u = u->next;
			}
			u->A.push_back(A[i]);
		}
		for (u = head; u != NULL; u = u->next)
			u->relax();
		return head;
	}
	Node* newNode() {
		Node* p = new Node();
		return p;
	}
	Node* cloneNode(Node *u) {
		Node *t = u->real();
		Node *p = new Node();
		*p = *t, p->next = u->next;
		return p; 
	}
	Node* aliasNode(Node *u) {
		Node *t = u->real();
		Node* p = new Node();
		p->alias = t, p->next = u->next;
		return p;
	}
	Node* erase(Node *ver, int x) {
		Node *a, *b, *u, *v, *t;
		u = ver, a = NULL;
		for (int l = 1, r; u; l = r+1, u = u->next) {
			r = l + u->real()->A.size() - 1;
			if (l <= x && x <= r) {
				t = cloneNode(u);
				if (a == NULL)
					a = t, b = a;
				else
					b->next = t, b = b->next;
				t->erase(x - l);
				t->next = u->next;
				break;
			} else {
				if (a == NULL)
					a = aliasNode(u), b = a;
				else
					b->next = aliasNode(u), b = b->next;
			}
		}
		return relaxList(a);
	}
	Node* insert(Node *ver, int x, int val) {
		Node *a, *b, *u, *v, *t;
		u = ver, a = NULL;
		for (int l = 1, r; u; l = r+1, u = u->next) {
			r = l + u->real()->A.size() - 1;
			if (l-1 <= x && x <= r) {
				t = cloneNode(u);
				if (a == NULL)
					a = t, b = a;
				else
					b->next = t, b = b->next;
				t->insert(x - l + 1, val);
				t->next = u->next;
				x = -1;
			} else {
				if (a == NULL)
					a = aliasNode(u), b = a;
				else
					b->next = aliasNode(u), b = b->next;
			}
		}
		return relaxList(a);
	}
	Node* change(Node *ver, int x, int val) {
		Node *a, *b, *u, *v, *t;
		u = ver, a = NULL;
		for (int l = 1, r; u; l = r+1, u = u->next) {
			r = l + u->real()->A.size() - 1;
			if (l <= x && x <= r) {
				t = cloneNode(u);
				if (a == NULL)
					a = t, b = a;
				else
					b->next = t, b = b->next;
				t->change(x - l, val);
				t->next = u->next;
				break;
			} else {
				if (a == NULL)
					a = aliasNode(u), b = a;
				else
					b->next = aliasNode(u), b = b->next;
			}
		}
		return relaxList(a);
	}
	int findRank(Node *ver, int L, int R, int val) {
		Node *u, *v;
		int ret = 0;
		u = ver;
		for (int l = 1, r; u != NULL; u = u->next, l = r+1) {
			r = l + u->real()->A.size() - 1;
			if (L <= l && r <= R) {
				ret += upper_bound(u->real()->B.begin(), u->real()->B.end(), val) - u->real()->B.begin();
				L = r + 1;
			} else if ((l <= L && L <= r) || (l <= R && R <= r)) {
				int i = L - l;
				while (i < u->real()->A.size() && L <= R) {
					if (u->real()->A[i] <= val)
						ret++;
					i++, L++;
				}
			}
		}
		return ret;
	}
	int find(Node *ver, int L, int R, int k)  {	// kth-number
		int l = 0, r = 100000, mid, t = 0; // value in A[]
		while (l <= r) {
			mid = (l + r)/2;
			if (findRank(ver, L, R, mid) >= k)
				r = mid - 1, t = mid;
			else
				l = mid + 1;
		}
		return t;
	}
	Node* mergeNode(Node *u, Node *v) {
		Node *p, *q;
		Node *a = newNode();
		p = u->real(), q = v->real();
		a->next = v->next;
		a->A.insert(a->A.end(), p->A.begin(), p->A.end());
		a->A.insert(a->A.end(), q->A.begin(), q->A.end());
		a->relax();
		return a;
	}
	Node* splitNode(Node *u) {
		Node *t = u->real();
		Node *a = newNode(), *b = newNode();
		int n = t->A.size()/2;
		a->next = b, b->next = u->next;
		a->A.insert(a->A.begin(), t->A.begin(), t->A.begin()+n);
		b->A.insert(b->A.begin(), t->A.begin()+n, t->A.end());
		a->relax(), b->relax();
		return a;
	}
	Node* relaxList(Node *ver) {
	    Node *a, *b, *u, *v, *t;
	    u = ver, a = NULL;
	    for (u = ver; u != NULL; u = u->next) {
	        if (u->next != NULL && u->real()->A.size() + u->next->real()->A.size() < 2 * PSIZE) {	// merge
	        	if (a == NULL)
	        		a = mergeNode(u, u->next), b = a;
	        	else
	        		b->next = mergeNode(u, u->next), b = b->next;
				u = u->next;
	        } else if (u->real()->A.size() > 2 * PSIZE) {	// split
	        	if (a == NULL)
	        		a = splitNode(u), b = a->next;
	        	else
	        		b->next = splitNode(u), b = b->next->next;
	        } else {
	        	if (a == NULL)	
					a = aliasNode(u), b = a;
	        	else			
					b->next = aliasNode(u), b = b->next;
	        }
	    }
	    return a;
	}
	void debug(Node *head) {
		Node *u = head;
		printf("[");
    	while (u != NULL) {
        	for(int i = 0; i < u->real()->A.size(); i++)
            	printf("%d%s", u->real()->A[i], i != u->real()->A.size()-1 ? " " : " ");
        	u = u->next;
    	}
//    	puts(" A");
//    	u = head;
//    	while (u != NULL) {
//    		printf("[");
//        	for(int i = 0; i < u->real()->B.size(); i++)
//            	printf("%d%s", u->real()->B[i], i != u->real()->B.size()-1 ? " " : "");
//        	printf("]");
//        	u = u->next;
//    	}
//    	puts(" B\n==== debug");
    	puts("]");
	}
	void free(Node *head) {
		Node *u = head, *v = NULL;
    	while(u != NULL) {
        	v = u, u = u->next;
        	delete v;
    	}
	}
} dream; 

int A[MAXN], n, q;
UnrolledLinkedList::Node *ver[MAXQ];
int main() {
	int x, y, v, cmd;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		ver[0] = dream.init(A, n);
//		dream.debug(ver[0]);
		int encrypt = 0;
		scanf("%d", &q);
		for (int i = 1; i <= q; i++) {
			scanf("%d", &cmd);
			cmd ^= encrypt;
			if (cmd == 0) {			// back version v
				scanf("%d", &v);
				v ^= encrypt;
				ver[i] = ver[v];
			} else if (cmd == 1) { 	// insert A[x] = v
				scanf("%d %d", &x, &v);
				x ^= encrypt, v ^= encrypt;
				ver[i] = dream.insert(ver[i-1], x, v);
			} else if (cmd == 2) {	// delete A[x]
				scanf("%d", &x);
				x ^= encrypt;
				ver[i] = dream.erase(ver[i-1], x);
			} else if (cmd == 3) {	// make A[x] = v
				scanf("%d %d", &x, &v);
				x ^= encrypt, v ^= encrypt;
				ver[i] = dream.change(ver[i-1], x, v);
			} else if (cmd == 4) {
				scanf("%d %d %d", &x, &y, &v);
				x ^= encrypt, y ^= encrypt, v ^= encrypt;
				int t = dream.find(ver[i-1], x, y, v);
				printf("%d\n", t);
				encrypt = t;
				ver[i] = ver[i-1];
			} else {
				puts("WTF");
				return 0;
			}
//			dream.debug(ver[i]);
		}
	}
	return 0;
}
/*
5
1 2 3 4 5
9999
4 1 5 2
1 2 1
4 1 5 2
0 1
4 1 5 2
2 1
1 0 5
3 3 9
4 1 1 1

*/
