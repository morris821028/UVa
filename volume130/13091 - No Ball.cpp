#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		char g[5][8];
		for (int i = 0; i < 5; i++)
			scanf("%s", g[i]);
		
		int bpos = 0, vpos = 0, vdir = 0;
		for (int i = 0; i < 5; i++) {
			if (g[0][i] == '|')
				bpos = i;
			for (int j = 0; j < 5; j++) {
				if (g[i][j] == '.' || g[i][j] == '|')
					continue;
				vpos = j, vdir = g[i][j] == '>';
			}
		}
		
		printf("Case %d: ", ++cases);
		if ((vdir && vpos > bpos) || 
			(!vdir && vpos < bpos))
			puts("No Ball");
		else
			puts("Thik Ball");
	}
	return 0;
}

