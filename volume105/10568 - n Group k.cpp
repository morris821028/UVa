#include <stdio.h> 
#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
unsigned long long C[32][32];
unsigned long long calcWays(int n, int m) {
	unsigned long long ret = C[n][n%m];
	n = n - n%m;
	for (int i = n/m - 1; i >= 0; i--)
		ret *= C[n-1][m-1], n -= m;
	return ret;
}

int used[26] = {};
vector<string> group, path;
void generate(int idx, int end, int n, int m) {
	if (idx == end) {
		vector<string> tmp = path;
		sort(tmp.begin(), tmp.end());
		string comb = tmp[0];
		for (int i = 1; i < tmp.size(); i++)
			comb = comb + " " + tmp[i];
		group.push_back(comb);
		return ;
	}
	int A[26] = {}, B[26], bn = 0;
	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			B[bn++] = i;
		}
	}
	for (int i = m; i < bn; i++)
		A[i] = 1;
	used[B[0]] = 1;
	do {
		string f = "";
		f += (char)(B[0] + 'A');
		for (int i = 1; i < bn; i++) {
			if (!A[i]) {
				used[B[i]] = 1;
				f += (char)(B[i] + 'A');
			}
		}
		path.push_back(f);
		generate(idx + 1, end, n, m);
		path.pop_back();
		for (int i = 1; i < bn; i++)
			if (!A[i])
				used[B[i]] = 0;		
	} while (next_permutation(A + 1, A + bn));
	used[B[0]] = 0;
}
int main() {
	for (int i = 0; i < 32; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
	char cmd[32];
	int n, m;
	while (scanf("%s %d %d", cmd, &n, &m) == 3) {
		if (!strcmp(cmd, "END"))
			break;
		printf("%llu\n", calcWays(n, m));
		if (cmd[0] == 'C') {
			
		} else {
			group.clear();
			int A[26] = {};
			for (int i = n%m; i < n; i++)
				A[i] = 1;
			do {
				memset(used, 0, sizeof(used));
				string f = "";
				path.clear();
				for (int i = 0; i < n; i++) {
					if (!A[i]) {
						used[i] = 1;
						f += (char)(i + 'A');
					}
				}
				if (f.length())
					path.push_back(f);
				generate(0, (n - n%m)/m, n, m);
			} while (next_permutation(A, A+n));
			sort(group.begin(), group.end());
			for (int i = 0; i < group.size(); i++)
				puts(group[i].c_str());
		}
	}
	return 0;
}
