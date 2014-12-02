#include <stdio.h>
char SMS[10][10] = {" ",
	".,?\"", "abc", "def",
	"ghi", "jkl", "mno",
	"pqrs", "tuv", "wxyz"
};
int main() {
	int testcase, n, A[128], B[128];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < n; i++)
			scanf("%d", &B[i]);
		for (int i = 0; i < n; i++)
			putchar(SMS[A[i]][B[i] - 1]);
		puts("");
	}
	return 0;
}
