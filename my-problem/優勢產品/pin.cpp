#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
	int testcase, n, m, x, y;
	testcase = 30;
    printf("%d\n\n", testcase);
	while (testcase--) {
        int n = 1000, m = 7, k = rand()%2 + 4;
        printf("%d %d %d\n", n, m, k);
        for (int i = 0; i < n; i++) {
            int sum = rand()%(m*1000 - 500);
            int th = 800;
            vector<int> A;
            for (int j = 0; j < m; j++) {
                int s = min(rand()%th, sum) + 1;
                A.push_back(s);
                sum -= s;
                sum = max(sum, 0);
            }
            random_shuffle(A.begin(), A.end());
            for (int j = 0; j < m; j++) {
                int s = A[j];
                printf("%d%c", s, j == m-1 ? '\n' : ' ');
            }
        }
        printf("\n");
	}
	return 0;
}