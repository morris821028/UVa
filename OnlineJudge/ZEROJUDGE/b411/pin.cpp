#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
using namespace std;

int main() {
	 srand (time(NULL));
	int testcase, n, m, x, y;
    testcase = 1;
	freopen("in.txt", "w+t", stdout);
//    printf("%d\n", testcase);
	while (testcase--) {
        n = 30;
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%d%c", rand()%1000, i == n-1 ? '\n' : ' ');
        }
        m = 100;
        printf("%d\n", m);
        vector<int> L;
        L.push_back(n);
        for (int i = 1; i <= m; i++) {
            while (true) {
                int cmd = rand()%4 + 1;
                if (n == 1 && cmd == 2)
                    continue;
                if (cmd == 0) {
                	int x = rand()%i;
                	printf("%d %d\n", cmd, x);
                	n = L[x];
                }
                if (cmd == 1)
                    printf("%d %d %d\n", cmd, rand()%(n+1), rand()%1000), n++;
                if (cmd == 2)
                    printf("%d %d\n", cmd, rand()%n+1), n--;
                if (cmd == 3)
                    printf("%d %d %d\n", cmd, rand()%(n+1), rand()%1000);
                if (cmd == 4) {
                    x = rand()%n+1, y = rand()%n+1;
                    if (x > y)  swap(x, y);
                    printf("%d %d %d %d\n", cmd, x, y, rand()%(y - x + 1) + 1);
                }
                break;
            }
            L.push_back(n);
        }
	}
	return 0;
}
