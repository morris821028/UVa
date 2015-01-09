#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

int SG[1024];
void buildSG() {
	int mex[1024] = {};
	SG[0] = 0;
	for (int i = 1; i < 50; i++) {
		memset(mex, 0, sizeof(mex));
		for (int j = 0; j < i; j++) {
			mex[SG[j] ^ SG[i-j-1]] = 1;
			if (i-j-2 >= 0)
				mex[SG[j] ^ SG[i-j-2]] = 1;
		}
		int sg = 0;
		for (sg; mex[sg]; sg++);
		SG[i] = sg;
	}
}
int main() {
	buildSG();
	int testcase, cases = 0, n, m, x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		int used[64] = {}, last = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			x--;
			used[last = x] = 1;
		}
		
		vector<int> nim;
		for (int i = 0, tmp = 0, pos; i < n; i++) {
			pos = (last + i)%n;
			if (used[pos] == 0)
				tmp++;
			if (used[pos] || i == n-1) {
				if (tmp)
					nim.push_back(tmp);
				tmp = 0;
			}
		}
		
		int ret = 0;
		for (int i = 0; i < nim.size(); i++)
			ret ^= SG[nim[i]];
		printf("Case %d: %s\n", ++cases, ret ? "yes" : "no");
	}
	return 0;
}
/*
9999
13 1
7

5 3
1 3 4

6 2
1 5

1 1
1

1 0

*/
