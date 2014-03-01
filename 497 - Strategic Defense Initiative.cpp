#include <stdio.h>
#include <string.h>

struct LIS {
	int A[1000], n, maxLIS;
	int pos[1000], lis[1000];
	void findLIS() {
		int i, l, m, r, newSet;
		maxLIS = -1;
		for(i = 0; i < n; i++) {
			l = 0, r = maxLIS, newSet = -1;
			while(l <= r) {
				m = (l+r)/2;
				if(pos[m] <= A[i]) {
					if(m == maxLIS || pos[m+1] > A[i]) {
						newSet = m+1;
						break;
					} else
						l = m+1;
				} else
					r = m-1;
			}
			if(newSet == -1)
				newSet = 0;
			pos[newSet] = A[i];
			lis[i] = newSet+1;
			if(maxLIS < newSet)
				maxLIS = newSet;
		}
		maxLIS++;
	}
	void printLIS() {
		int ans[1000], at = 0, i, tmp = maxLIS;
		for(i = n-1; i >= 0; i--) {
			if(lis[i] == tmp)
				tmp--, ans[at++] = A[i];
		}
		for(i = at-1; i >= 0; i--)
			printf("%d\n", ans[i]);
	}
};
int main() {
	int t, n;
	char str[100];
	LIS data;
	scanf("%d", &t);
	getchar();
	getchar();
	while(t--) {
		n = 0;
		while(gets(str)) {
			if(str[0] == '\0')
				break;
			sscanf(str, "%d", &data.A[n]);
			n++;
		}
		data.n = n;
		data.findLIS();
		printf("Max hits: %d\n", data.maxLIS);
		data.printLIS();
		if(t)
			puts("");
	}
    return 0;
}
