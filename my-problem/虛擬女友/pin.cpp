#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
using namespace std;

int main() {
	 srand (time(NULL));
	int testcase, n, m, x, y;
    int A[100];
	testcase = 3;
    printf("%d\n\n", testcase);
	while (testcase--) {
        n = 50000, m = 50000;
        printf("%d %d\n", n, m);
        for (int i = 0; i < n; i++) {
            printf("%d%c", rand()%256+1, i == n-1 ? '\n' : ' ');
        }
        for (int i = 1; i <= m; i++) {
            int x, y;
            do {
                x = rand()%n + 1, y = rand()%n + 1;
            } while (x == y);
            printf("%d %d\n", x, y);
        }
        if (testcase)
            puts("");
	}
	return 0;
}