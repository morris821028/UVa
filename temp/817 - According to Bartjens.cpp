#include <stdio.h> 
#include <string.h>
using namespace std;
int n, sol;
char s[1024], path[1024];
char op[] = "*+-";
void check2000(char expr[]) {
	int n = strlen(expr);
	int A[20] = {}, idx = 0;
	char preOp = '+';
	for (int i = 0; i < n; ) {
		if (expr[i] >= '0' && expr[i] <= '9') {
			if (expr[i] == '0' && expr[i+1] >= '0' && expr[i+1] <= '9')
				return; // 01, 001, ...
			int num = 0;
			while (expr[i] >= '0' && expr[i] <= '9')
				num = num * 10 + expr[i] - '0', i++;
			if (preOp == '*')	
				A[idx-1] *= num;
			else if (preOp == '+')
				A[idx++] = num;
			else if (preOp == '-')
				A[idx++] = -num;
		} else {
			preOp = expr[i], i++;
		}
	}
	int sum = 0;
	for (int i = 0; i < idx; i++)
		sum += A[i];
	if (sum == 2000)
		printf("  %s=\n", expr), sol++;
}
void dfs(int idx, int pl, int n) {
	if (idx == n) {
		path[pl] = '\0';
		if (pl > n)
		check2000(path);
		return ;
	}
	if (idx != n-1) {
		for (int i = 0; i < 3; i++) {
			path[pl] = s[idx], path[pl + 1] = op[i];
			dfs(idx+1, pl+2, n);
		}
	}
	path[pl] = s[idx];
	dfs(idx+1, pl+1, n);
}
int main() {
	int cases = 0;
	while (scanf("%s", s) == 1) {
		if (!strcmp(s, "="))
			break;
		n = strlen(s);
		s[n - 1] = '\0';
		n--, sol = 0;
		printf("Problem %d\n", ++cases);
		dfs(0, 0, n);
		if (sol == 0)
			puts("  IMPOSSIBLE");
	}
	return 0;
}
