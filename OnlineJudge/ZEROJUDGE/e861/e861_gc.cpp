#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct PStack : std::enable_shared_from_this<PStack<T>> {
	T elem;	
	shared_ptr<PStack<T>> next;
	int sz;

	PStack(): sz(0), elem(), next(nullptr) {}
	PStack(T elem, shared_ptr<PStack<T>> next, int sz):
		sz(sz), elem(elem), next(next) {}
	
	T top() const { return elem; }

	shared_ptr<PStack<T>> push(T elem) {
		return make_shared<PStack<T>>(elem, this->shared_from_this(), sz + 1);
	}

	shared_ptr<PStack<T>> pop() const {
		if (next != nullptr)
			return next;
		return nullptr;
	}

	int size() {
		return sz;
	}

	static shared_ptr<PStack<T>> empty() {
		static shared_ptr<PStack<T>> ptr = make_shared<PStack<T>>();
		return ptr;
	}
};

const int MAXOPT = 1000005;

shared_ptr<PStack<int>> vers[MAXOPT];
int main() {
	vers[0] = PStack<int>::empty();

	int cmd, v, x;
	int ver = 0;
	while (scanf("%d", &cmd) == 1) {
		ver++;
		if (cmd == 0) {
			scanf("%d", &v);
			vers[ver] = vers[v];
		} else if (cmd == 1) {
			scanf("%d", &x);
			vers[ver] = vers[ver-1]->push(x);
		} else if (cmd == 2) {
			vers[ver] = vers[ver-1]->pop();
		} else {
			vers[ver] = vers[ver-1];
			shared_ptr<PStack<int>> ptr = vers[ver];
			int size = ptr->size();
			for (int i = 0; i < size && i < 3; i++) {
				printf("%d ", ptr->top());
				ptr = ptr->pop();
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
