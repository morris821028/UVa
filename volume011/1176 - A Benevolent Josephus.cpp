#include <bits/stdc++.h>
using namespace std;

//int josephus(int n, int m) {
//    int s = 0;
//    for (int i = 2; i <= n; i++)
//        s = (s+m)%i;
//    return s+1;
//}

int main() {
	const int MAXN = 65536;
	int J[MAXN] = {}, D[MAXN] = {};
	for (int i = 2; i < MAXN; i++)
		J[i] = (J[i-1]+2)%i;
	for (int i = 1; i < MAXN; i++) {
		J[i] = J[i]+1;
		if (J[i] == i)
			D[i] = 2*i;
		else
			D[i] = i-J[i] + D[J[i]];
	}
	int n;
	while (scanf("%d", &n) == 1) {
		int ret = D[n];
		printf("%d\n", ret);
	}
	return 0;
}
