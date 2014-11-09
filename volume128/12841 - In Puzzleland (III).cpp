#include <stdio.h>
#include <iostream>
#include <set> 
#include <algorithm>
using namespace std;

int main() {
	int testcase, cases = 0;
	int n, m, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		char name[26][4], s1[4], s2[4], buf[26];
		int g[26][26] = {};
		for (int i = 0; i < n; i++)
			scanf("%s", name[i]);
		for (int i = 0; i < m; i++) {
			scanf("%s %s", s1, s2);
			x = s1[0] - 'A', y = s2[0] - 'A';
			g[x][y] = g[y][x] = 1;
		}
		int st = name[0][0] - 'A', ed = name[n-1][0] - 'A';
		set<string> dp[1<<16];
		for (int i = (1<<n) - 1; i > 0; i--) {
			int A[16], m = 0;
			for (int j = 0; j < n; j++) {
				if ((i>>j)&1)
					A[m++] = name[j][0] - 'A';
			}
			if (m == n/2) {
				int ok = 0, idx = 0;
				for (int j = 0; j < m; j++) {
					if (A[j] == st)
						ok = 1, idx = j;
				}
				if (ok) {
					swap(A[0], A[idx]);
					sort(A+1, A+m);
					do {
						int ok = 1;
						for (int j = 1; j < m; j++)
							if (!g[A[j]][A[j-1]])
								ok = 0;
						if (ok) {
							for (int j = 0; j < m; j++)
								buf[j] = A[j] + 'A';
							buf[m] = '\0';
							dp[i].insert(buf);
						}
					} while (next_permutation(A+1, A+m));
				}
			}
			if (m == n - n/2) {				
				int ok = 0, idx = 0;
				for (int j = 0; j < m; j++) {
					if (A[j] == ed)
						ok = 1, idx = j;
				}
				if (ok) {
					swap(A[m-1], A[idx]);
					sort(A, A+m-1);
					do {
						int ok = 1;
						for (int j = 1; j < m; j++)
							if (!g[A[j]][A[j-1]])
								ok = 0;
						if (ok) {
							for (int j = 0; j < m; j++)
								buf[j] = A[j] + 'A';
							buf[m] = '\0';
							dp[i].insert(buf);
						}
					} while (next_permutation(A, A+m-1));
				}
			}
		}
		printf("Case %d: ", ++cases);
		string ret = "";
		for (int i = (1<<n) - 1; i >= 0; i--) {
			for (set<string>::iterator it = dp[i].begin(); it != dp[i].end(); it++) {
				if ((*it)[0] == st + 'A') {
					if (ret != "" && ret < *it)	break;
					for (set<string>::iterator jt = dp[((1<<n)-1)^i].begin(); 
						jt != dp[((1<<n)-1)^i].end(); jt++) {
						if (g[(*it)[it->length()-1]-'A'][(*jt)[0]-'A']) {
							if (ret == "" || ret > *it + *jt)
								ret = *it + *jt;
						}
					}
				}
			}
			
		}
		if (ret == "")
			puts("impossible");
		else {
			puts(ret.c_str());
		}
	}
	return 0;
}
/*
3
12 14
A B C D E F U V W X Y Z
A F
A V
B U
B W
C D
C V
D Y
D W
E X
E Z
F U
F Y
U Z
W X
3 2
A B C
A B
A C
4 5
L N I K
L N
I L
I N
K N
K I
*/
