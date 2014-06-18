#include <stdio.h>

int main() {
	int n;
	char s[105];
	int A[105];
	while(scanf("%d", &n) == 1 && n) {
		scanf("%s", s);
		for(int i = 0; i < n; i++) {
			scanf("%d", &A[i]);
		}
		if(s[0] == 'p') {
			for(int i = 0; i < n; i++) {
				int cnt = 0;
				for(int j = 0; j < i; j++) {
					if(A[j] < A[i])
						cnt++;
				}
				printf("%d%c", cnt, i == n-1 ? '\n' : ' ');
			}
		} else {
			int B[105] = {};
			for(int i = 0; i < n; i++)
				B[i] = -1;
			for(int i = n-1; i >= 0; i--) {
				if(A[i] == 0) {
					B[i] = 0;
					break;
				}
			}
			for(int i = 1; i < n; i++) {
				for(int j = n-1; j >= 0; j--) {
					if(B[j] != -1)	continue;
					int cnt = 0;
					for(int k = 0; k < j; k++) {
						if(B[k] != -1)
						cnt += B[k] < i;
					}
					if(B[j] == -1 && A[j] == cnt) {
						B[j] = i;
						break;
					}
				}
			}			
			for(int i = 0; i < n; i++) {
				printf("%d%c", B[i], i == n-1 ? '\n' : ' ');
			}
		}
	}
	return 0;
}
