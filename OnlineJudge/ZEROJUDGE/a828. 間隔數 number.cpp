#include <bits/stdc++.h>
using namespace std;

int main() {
	vector< pair<int, int> > A;
	for (int i = 1; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			if (i != j)
				A.push_back(make_pair(i, j));
	}
	
	int n;
	while (scanf("%d", &n) == 1) {
		int len = (n-1)/A.size() + 3;
		int kind = (n-1)%A.size();
		for (int i = 0; i+2 <= len; i += 2)
			printf("%d%d", A[kind].first, A[kind].second);
		if (len%2)
			printf("%d", A[kind].first);
		puts("");
	}
	return 0;
}
