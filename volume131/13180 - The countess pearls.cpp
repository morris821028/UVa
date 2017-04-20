#include <bits/stdc++.h>
using namespace std;

int main() {
	static int A[1024];
	while (scanf("%d", &A[0]) == 1 && A[0]) {
		int n = 1;
		while (scanf("%d", &A[n]) == 1 && A[n])
			n++;
		sort(A, A+n);
		int ok = 1, prev = -1;
		for (int i = 0; i+1 < n; i += 2)
			ok &= A[i] == A[i+1];
		if (!ok || n%2 == 0) {
			puts("NO");
		} else {
			int m = n;
			for (int i = 0; i+1 < n; i += 2)
				printf("%d%c", A[i], "\n "[(--m)!=0]);
			if (n&1)
				printf("%d%c", A[n-1], "\n "[(--m)!=0]);
			for (int i = n/2*2-1; i >= 0; i -= 2)
				printf("%d%c", A[i], "\n "[(--m)!=0]);
		}
	}
	return 0;
}

