#include <stdio.h>
#include <string.h>
#pragma GCC optimize ("O3")
class HASH {
#define HSIZE 300007
#define HNODE 131072
	public:
	struct Node {
		int first, second;
		Node(int a = 0, int b = 0):
			first(a), second(b) {}
	};
	int head[HSIZE], next[HNODE], nsize;
	Node nodes[HNODE];
	void clear() {
		memset(head, -1, sizeof(head));
		nsize = 0;
	}
	Node* insert(Node s, int hidx = -1) {
		if (hidx == -1)		hidx = s.first%HSIZE;
		nodes[nsize] = s;
		next[nsize] = head[hidx];
		head[hidx] = nsize;
		return &nodes[nsize++];
	}
	void update(Node s) {
		static int hidx;
		hidx = s.first%HSIZE;
		for(int i = head[hidx]; i != -1; i = next[i]) {
			if(nodes[i].first == s.first) {
				nodes[i].second = s.second;
				return;
			}
		}
		insert(s, hidx);
	}
	Node* get(int key) {
		static int hidx;
		hidx = key%HSIZE;
		for(int i = head[hidx]; i != -1; i = next[i]) {
			if(nodes[i].first == key)
				return &nodes[i];
		}
		return insert(Node(key, 0), hidx);
	}
} hash;
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	int testcase, n, x;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d", &n);
		ReadInt(&n);
		hash.clear();
		int low = 0;
		long long ret = 0;
		HASH::Node *s;
		for (int i = 1; i <= n; i++) {
//			scanf("%d", &x);
			ReadInt(&x);
			s = hash.get(x);
			if (s->second > low)	low = s->second;
			s->second = i;
			ret += i - low;
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
9
3
1 2 1
5
1 2 3 1 2
4
1 2 2 1
*/
