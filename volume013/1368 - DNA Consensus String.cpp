#include <stdio.h> 
#include <algorithm>
using namespace std;

int main() {
	int testcase;
	int n, m;
	char DNA[64][1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", DNA[i]);
		int hh = 0;
		char ret[1024] = {}, cc[] = "ACGT";
		for (int i = 0; i < m; i++) {
			int cnt[4] = {}, mx = 0;
			for (int j = 0; j < n; j++)
				cnt[find(cc, cc+4, DNA[j][i]) - cc]++;
			
			for (int j = 0; j < 4; j++) {
				if (cnt[j] > cnt[mx])
					mx = j;
			}
			ret[i] = cc[mx], hh += n - cnt[mx];
				
		}
		printf("%s\n%d\n", ret, hh);
	}
	return 0;
}
