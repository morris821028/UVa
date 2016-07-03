#include <stdio.h> 
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;

class HASH {
public:
#define HSIZE 1403641
#define HNODE (2097152 + 10)
	struct Node {
		long long first;
		int second;
		Node(long long a = 0, int b = 0):
			first(a), second(b) {}
	};
	int head[HSIZE], next[HNODE], size;
	Node nodes[HNODE];
	
	unsigned long hash(unsigned long key) {
		key = ~key + (key << 15); // key = (key << 15) - key - 1;
  		key = key ^ (key >> 12);
  		key = key + (key << 2);
  		key = key ^ (key >> 4);
  		key = key * 2057; // key = (key + (key << 3)) + (key << 11);
  		key = key ^ (key >> 16);
  		return key % HSIZE;
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
	int& operator[](long long x) {
		static int i, hidx;
		hidx = hash(x);
		for (i = head[hidx]; i != -1; i = next[i]) {
			if (nodes[i].first == x)
				return nodes[i].second;
		}
		return add(hidx, Node(x, 0)).second;
	}
} hash;

int n;
long long m, A[64], sum[1<<20];
void meetInMiddle() {
	sort(A, A+n);
	// D&C, dp, bitmask
	long long ret = 0;
	int div1 = n/2, div2 = n - n/2;
	
	hash.init();
	
	for (int i = 0; i < div1; i++)
		sum[1<<i] = A[i];
	for (int i = 0; i < (1<<div1); i++) {
		sum[i] = sum[i - ((i-1)&i)] + sum[(i-1)&i];
		long long x = sum[i];
		hash[x]++;
	}
	for (int i = 0; i < div2; i++)
		sum[1<<i] = A[i + div1];
	for (int i = 0; i < (1<<div2); i++) {
		sum[i] = sum[i - ((i-1)&i)] + sum[(i-1)&i];
		long long x = sum[i];
		ret += hash[m - x];
	}
	if (m == 0)		ret--;
	printf("%lld\n", ret);
}
int main() {
	while (scanf("%d %lld", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%lld", &A[i]);
		
		meetInMiddle();
	}
	return 0;
}
/*
6 0
-1 2 -3 4 -5 6
5 0
-7 -3 -2 5 8
40 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
5 2
1 1 1 1 1
6 1
1 2 3 -2 -1 -3
6 -1
0 0 0 0 0 0
*/
