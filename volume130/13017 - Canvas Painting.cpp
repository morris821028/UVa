#include <bits/stdc++.h>
using namespace std;
// Huffman Coding, Greedy
// input A[1...n]
// minimum \sum A[i]*code[i]
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, x;
		long long t;
		multiset<long long> S;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &x), S.insert(x);
			
		long long ret = 0;
		for (int i = n-2; i >= 0; i--) {
			long long a, b;
			a = *S.begin();
			S.erase(S.begin());
			b = *S.begin();
			S.erase(S.begin());
			ret += a+b;
			S.insert(a+b);
		}
		printf("%lld\n", ret);
	}
	return 0;
}

