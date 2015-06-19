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

int A[4][262144];
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < 4 * n; i++) {
			char s[50];
			scanf("%s", s);
			int c = suit(s[0]), x;
			sscanf(s+1, "%d", &x);
			A[c][x] = i;
		}
		
		int round = 0;
		for (int i = 0; i < 4; i++) {
			int r = 1;
			for (int j = 1; j < n; j++) {
				if (A[i][j] > A[i][j+1])
					r++;
			}
			round = max(round, r);
		}
		printf("%d\n", round);
	}
	return 0;
}
/*
13
C3 H1 D1 S6 D2 S2 S5 H7 H4 H8 H9 C5 H2 D8 H6 S9 H12 H3 C6 S4 C9 C10 H10 C8 H13 C4 D9 S11 C12 H5 D10 S1 H11 C13 C11 S8 S7 D5 S10 C7 S12 S3 D4 C1 D11 S13 D6 C2 D13 D12 D3 D7
*/
