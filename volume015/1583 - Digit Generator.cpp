#include <stdio.h> 
#include <algorithm>
#include <string.h>
using namespace std;

int A[131072];
int main() {
	char s[1024];
	for (int i = 1; i < 131072; i++)
		A[i] = 0x3f3f3f3f;
	for (int i = 1; i < 131072; i++) {
		sprintf(s, "%d", i);
		int sum = i;
		for (int j = 0; s[j]; j++)
			sum += s[j] - '0';
		A[sum] = min(A[sum], i);
	}
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		printf("%d\n", A[n] == 0x3f3f3f3f ? 0 : A[n]);
	}
	return 0;
}
