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
	testcase = 1;
	freopen("in.txt", "w+t", stdout);
//    printf("%d\n", testcase);
	while (testcase--) {
        n = 32;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%d%c", rand(), i == n-1 ? '\n' : ' ');
        }
        m = 1000;
        printf("%d\n", m);
        vector<int> L;
        L.push_back(n);
        for (int i = 1; i <= m; i++) {
            while (true) {
                int cmd = rand()%8;
                if (n == 1 && cmd == 2)
                    continue;
                if (cmd == 0) {
                	int x = rand()%i;
                	printf("%d %d\n", cmd, x);
                	n = L[x];
                }
                if (cmd == 1)
                    printf("%d %d %d\n", cmd, rand()%(n+1), rand()), n++;
                if (cmd == 2)
                    printf("%d %d\n", cmd, rand()%n+1), n--;
                if (cmd == 3) {
                    x = rand()%n+1, y = rand()%n+1;
                    if (x > y)  swap(x, y);
                    printf("%d %d %d\n", cmd, x, y);
                }
                if (cmd == 4) {
                    x = rand()%n+1, y = rand()%n+1;
                    if (x > y)  swap(x, y);
                    printf("%d %d %d %d\n", cmd, x, y, rand());
                }
                if (cmd == 5 || cmd == 6 || cmd == 7) {
                    x = rand()%n+1, y = rand()%n+1;
                    if (x > y)  swap(x, y);
                    printf("%d %d %d\n", cmd, x, y);
                }
                break;
            }
            L.push_back(n);
        }
	}
	return 0;
}
