#include <stdio.h>
#include <math.h>
#include <stack>
#include <assert.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 65536;
const int MAXQ = 65536;
int A[MAXN], n, q;
vector<int> ver[MAXQ];
int main() {
	int x, y, v, cmd;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		ver[0] = vector<int>(A+1, A+n+1);
		scanf("%d", &q);
		for (int i = 1; i <= q; i++) {
			scanf("%d", &cmd);
			ver[i] = ver[i-1];
			if (cmd == 0) {			// back version v
				scanf("%d", &v);
				ver[i] = ver[v];
			} else if (cmd == 1) { 	// insert A[x] = v
				scanf("%d %d", &x, &v);
				ver[i].insert(ver[i].begin() + x, v);
			} else if (cmd == 2) {	// delete A[x]
				scanf("%d", &x);
				ver[i].erase(ver[i].begin() + x - 1);
			} else if (cmd == 3) {	// make A[x] = v
				scanf("%d %d", &x, &v);
				ver[i][x-1] = v;
			} else if (cmd == 4) {
				scanf("%d %d %d", &x, &y, &v);
				vector<int> T(ver[i].begin()+x-1, ver[i].begin()+y);
				sort(T.begin(), T.end());
				printf("%d\n", T[v-1]);
			} else {
				puts("WTF");
				return 0;
			}
			printf("[");
			for (auto &x : ver[i])
				printf("%d ", x);
			printf("]\n");
//			dream.debug(ver[i]);
		}
	}
	return 0;
}
