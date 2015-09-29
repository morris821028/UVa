#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	int rs[128][128];
	char s[128][128][8];
	while (scanf("%d %d", &n, &m) == 2) {
		int rsum[128], csum[128];
		map<string, int> R;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				scanf("%s", &s[i][j]), R[s[i][j]] = 0;
			scanf("%d", &rsum[i]);
		}
		for (int j = 0; j < m; j++)
			scanf("%d", &csum[j]);
		
		int size = 0, equ = 0;
		for (map<string, int>::iterator it = R.begin();
			it != R.end(); it++)
			it->second = size++;
				
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				rs[i][j] = R[s[i][j]];
		}
		
		int has_solve[1024] = {}, varx[1024] = {};
		for (int it = 0; it < size; it++) {
			for (int i = 0; i < n; i++) {
				int un = 0, xid = -1, xval = 0;
				long long sum = 0;
				for (int j = 0; j < m; j++) {
					if (has_solve[rs[i][j]])
						sum += varx[rs[i][j]];
					else {
						if (rs[i][j] != xid)
							xid = rs[i][j], xval = 1, un++;
						else if (rs[i][j] == xid)
							xval++;
					}
				}
				if (un == 1) {
					has_solve[xid] = 1;
					varx[xid] = (rsum[i] - sum) / xval;
				}
			}
			for (int i = 0; i < m; i++) {
				int un = 0, xid = -1, xval = 0;
				long long sum = 0;
				for (int j = 0; j < n; j++) {
					if (has_solve[rs[j][i]])
						sum += varx[rs[j][i]];
					else {
						if (rs[j][i] != xid)
							xid = rs[j][i], xval = 1, un++;
						else if (rs[j][i] == xid)
							xval++;
					}
				}
				if (un == 1) {
					has_solve[xid] = 1;
					varx[xid] = (csum[i] - sum) / xval;
				}
			}
		}
		
		for (map<string, int>::iterator it = R.begin();
			it != R.end(); it++)
			printf("%s %d\n", it->first.c_str(), varx[it->second]);
	}
	return 0;
}
