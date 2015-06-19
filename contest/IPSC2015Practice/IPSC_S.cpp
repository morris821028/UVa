#include <bits/stdc++.h>
using namespace std;

int suit(char c) {
	switch(c) {
		case 'S': return 0;
		case 'H': return 1;
		case 'D': return 2;
		case 'C': return 3;
	}
}
int simulate(vector<string> &A, int B[]) {
	vector<string> trash;
	for (int i = 0; i < A.size(); i++) {
		int c = suit(A[i][0]), x;
		sscanf(A[i].c_str(), "%*[SHDC]%d", &x);
		if (B[c] == x-1)	B[c]++;
		else				trash.push_back(A[i]);
	}
	A = trash;
	return A.size() > 0;		
} 
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		vector<string> A;
		int B[4] = {};
		for (int i = 0; i < 4 * n; i++) {
			char s[50];
			scanf("%s", s);
			A.push_back(s);
		}
		
		int round = 0;
		do {
			round++;
		} while (simulate(A, B));
		printf("%d\n", round);
	}
	return 0;
}
