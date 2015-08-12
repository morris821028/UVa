#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, x;
	char cmd[8];
	vector<int> A, B, C;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s %d", cmd, &x);
		if (cmd[0] == 'A')
			A.push_back(x);
		else
			B.push_back(x);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &x);
		C.push_back(x);
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	sort(C.begin(), C.end());
	long long stat1 = 0, stat2 = 0;
	int Aidx = 0, Bidx = 0;
	vector<int> D;
	for (int i = 0; i < C.size(); i++) {
		x = C[i];
		if (Bidx < B.size()) {
			if (x > B[Bidx]) {
				Bidx++;
			} else {
				D.push_back(x);
			}
		} else {
			D.push_back(x);
		}
	}
	for (int i = 0; i < D.size(); i++) {
		x = D[i];
		if (Aidx < A.size()) {
			if (x >= A[Aidx]) {
				stat1 += x - A[Aidx];
				Aidx++;
			}
		} else {
			if (Bidx == B.size())
				stat1 += x;
		}
	}
	
	
	Aidx = 0;
	for (int i = C.size()-1; i >= 0; i--) {
		x = C[i];
		if (Aidx < A.size()) {
			if (x >= A[Aidx]) {
				stat2 += x - A[Aidx];
				Aidx++;
			}
		} else {
			if (B.size() == 0)
				stat2 += x;
		}
	}
	printf("%lld\n", max(stat1, stat2));
	return 0;
}
/*
2 3
ATK 2000
DEF 1700
2500
2500 
2500

3 4
ATK 10
ATK 100
ATK 1000
1
11
101
1001   
*/
