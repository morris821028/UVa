#include <bits/stdc++.h>
using namespace std;
const int MAXOPT = 100005;

stack<int> vers[MAXOPT];
int main() {
	vers[0] = stack<int>();

	int cmd, v, x;
	int ver = 0;
	while (scanf("%d", &cmd) == 1) {
		ver++;
		if (cmd == 0) {
			scanf("%d", &v);
			vers[ver] = vers[v];
		} else if (cmd == 1) {
			scanf("%d", &x);
			vers[ver] = vers[ver-1];
			vers[ver].push(x);
		} else if (cmd == 2) {
			vers[ver] = vers[ver-1];
			vers[ver].pop();
		} else {
			vers[ver] = vers[ver-1];
			stack<int> *ptr = &vers[ver];
			static stack<int> tmp;
			int size = ptr->size();
			for (int i = 0; i < size && i < 3; i++) {
				printf("%d ", ptr->top());
				tmp.push(ptr->top());
				ptr->pop();
			}
			while (!tmp.empty()) {
				ptr->push(tmp.top());
				tmp.pop();
			}
			if (size > 3)
				printf("... ");
			puts("]");
		}
	}
	return 0;
}

/*
1 1
1 2
3
0 1
3
1 3
3
0 3
3

1 3
1 2
1 1
3
1 0
3
0 0
3
*/
