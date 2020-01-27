#include <bits/stdc++.h>
using namespace std;
const int MAXOPT = 100005;

deque<int> vers[MAXOPT];
int main() {
	vers[0] = deque<int>();

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
			vers[ver].push_back(x);
		} else if (cmd == 2) {
			vers[ver] = vers[ver-1];
			vers[ver].pop_front();
		} else {
			vers[ver] = vers[ver-1];
			deque<int> *ptr = &vers[ver];
			static deque<int> tmp;
			int size = ptr->size();
			for (int i = 0; i < size && i < 3; i++) {
				printf("<%d", ptr->front());
				tmp.push_back(ptr->front());
				ptr->pop_front();
			}
			while (!tmp.empty()) {
				ptr->push_front(tmp.back());
				tmp.pop_back();
			}
			if (size > 3)
				puts("<...");
			else
				puts("");
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
