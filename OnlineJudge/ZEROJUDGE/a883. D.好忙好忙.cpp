#include <bits/stdc++.h>
using namespace std;

int main() {
	int x, y;
	pair<int, int> A[3];
	for (int i = 0; i < 3; i++) {
		scanf("%d %d", &x, &y);
		A[i] = {x, y};
	}
	sort(A, A+3);
	if (A[1].first >= A[0].second &&
		A[2].first >= A[1].second)
		puts("Happy");
	else
		puts("QQ");
	return 0;
}
