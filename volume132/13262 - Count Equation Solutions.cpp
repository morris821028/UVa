#include <bits/stdc++.h> 
using namespace std;
// meet in middle
class HASH {
public:
#define HSIZE 1403641
#define HNODE (2097152 + 10)
	struct Node {
		int first;
		int second;
		Node(int a = 0, int b = 0):
			first(a), second(b) {}
	};
	int head[HSIZE], next[HNODE], size;
	Node nodes[HNODE];
	
	unsigned long hash(unsigned long x) {
		return (x * 2654435761LU)% HSIZE;
	}
	void init() {
		memset(head, -1, sizeof(head));
		size = 0;
	}
	Node& add(int hidx, Node s) {
		nodes[size] = s;
		next[size] = head[hidx];
		head[hidx] = size;
		size++;
		return nodes[size-1];
	}
	int& operator[](int x) {
		int hidx = hash(x);
		for (int i = head[hidx]; i != -1; i = next[i]) {
			if (nodes[i].first == x)
				return nodes[i].second;
		}
		return add(hidx, Node(x, 0)).second;
	}
	int fetch(int x) {
		int hidx = hash(x);
		for (int i = head[hidx]; i != -1; i = next[i]) {
			if (nodes[i].first == x)
				return nodes[i].second;
		}
		return 0;
	}
} mHash;

int main() {
	int m;
	int a1, a2, a3, a4, a5, a6;
	while (scanf("%d", &m) == 1) {
		scanf("%d %d %d", &a1, &a2, &a3);
		scanf("%d %d %d", &a4, &a5, &a6);
		mHash.init();
		if (a5 > a1)	swap(a1, a5);
		if (a5 > a3)	swap(a3, a5);
		if (a3 > a1)	swap(a1, a3);
		if (a6 > a2)	swap(a2, a6);
		if (a6 > a4)	swap(a4, a6);
		if (a4 > a2)	swap(a2, a4);
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m; j++) {
				for (int k = 1; k <= m; k++) {
					int s = i*a1+j*a3+k*a5;
					mHash[s]++;
				} 
			}
		}
		
		int64_t ret = 0;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= m; j++) {
				for (int k = 1; k <= m; k++) {
					int s = i*a2+j*a4+k*a6;
					ret += mHash.fetch(s);
				}
			}
		}
		printf("%lld\n", ret);
	}
	return 0;
}
