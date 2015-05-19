// Anti-SG, Sprague Grundy - Jia Zhihao
#include <stdio.h> 

int main() {
	int testcase, cases = 0;
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		int sg = 0, s1 = 1;
		int x;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			sg ^= x;
			s1 &= x <= 1;
		}
		if (s1)
			printf("%s\n", sg == 0 ? "John" : "Brother");
		else
			printf("%s\n", sg ? "John" : "Brother");
	}
	return 0;
}
