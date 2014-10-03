#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

char exp[1048576];
map<long long, int> R;
void dfs(int l, int r, int dep) {
	if (exp[l] == '[') {
		int p = 0;
		for (int i = l + 1; i <= r - 1; i++) {
			if (exp[i] == '[')	p++;
			if (exp[i] == ']')	p--;
			if (p == 0 && exp[i] == ',') {
				dfs(l+1, i-1, dep+1);
				dfs(i+1, r-1, dep+1);
			}
		}
	} else {
		int w;
		exp[r+1] = '\0';
		sscanf(exp+l, "%d", &w);
		R[(long long)w<<dep]++;
	}
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", exp);
		R.clear();
		dfs(0, strlen(exp) - 1, 0);
		int sum = 0, mx = 0;
		for (map<long long, int>::iterator it = R.begin();
			it != R.end(); it++)
			sum += it->second, mx = max(mx, it->second);
		printf("%d\n", sum - mx);
	}
	return 0;
}
/*
3
[[3,7],6]
40
[[2,3],[4,5]]
*/
