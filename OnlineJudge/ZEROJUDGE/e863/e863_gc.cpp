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

template<typename T>
struct PQueue : std::enable_shared_from_this<PQueue<T>> {
	shared_ptr<PStack<T>> head;
	shared_ptr<PStack<T>> tail;
	
	shared_ptr<PStack<T>> tailRevFrom;
	shared_ptr<PStack<T>> tailRevTo;
	shared_ptr<PStack<T>> headRevFrom;
	shared_ptr<PStack<T>> headRevTo;
	int copied;
	
	PQueue(): PQueue(PStack<T>::empty(), PStack<T>::empty(),
		nullptr, nullptr, nullptr, nullptr, 0) {}
	PQueue(shared_ptr<PStack<T>> head,
			shared_ptr<PStack<T>> tail,
			shared_ptr<PStack<T>> tailRevFrom,
			shared_ptr<PStack<T>> tailRevTo,
			shared_ptr<PStack<T>> headRevFrom,
			shared_ptr<PStack<T>> headRevTo, int copied):
		head(head), tail(tail), tailRevFrom(tailRevFrom), tailRevTo(tailRevTo),
		headRevFrom(headRevFrom), headRevTo(headRevTo), copied(copied) {}
	
	int size() {
		int sz = head->size() + tail->size();
		if (tailRevTo != nullptr)
			sz += tailRevTo->size() + tailRevFrom->size() + copied;
		return sz;
	}

	T front() {
		return head->top();
	}

	shared_ptr<PQueue<T>> push(T elem) {
		return create(head, tail->push(elem), tailRevFrom, tailRevTo,
			headRevFrom, headRevTo, copied);
	}

	shared_ptr<PQueue<T>> pop() {
		if (size() == 1)
			return empty();
		return create(head->pop(), tail, tailRevFrom, tailRevTo,
			headRevFrom, headRevTo, copied);
	}

	shared_ptr<PQueue<T>> step(shared_ptr<PStack<T>> head, shared_ptr<PStack<T>> tail,
		shared_ptr<PStack<T>> tailRevFrom, shared_ptr<PStack<T>> tailRevTo,
		shared_ptr<PStack<T>> headRevFrom, shared_ptr<PStack<T>> headRevTo, int copied, int cost) {
		if (tailRevFrom != nullptr) {
			while (cost > 0) {
				cost--;
				if (headRevFrom->size() != 0) {
					headRevTo = headRevTo->push(headRevFrom->top());
					headRevFrom = headRevFrom->pop();
				} else if (tailRevFrom->size() != 0) {
					tailRevTo = tailRevTo->push(tailRevFrom->top());
					tailRevFrom = tailRevFrom->pop();
				} else if (tailRevFrom->size() == 0) {
					if (headRevTo->size() != 0 && copied < head->size()) {
						copied++;
						tailRevTo = tailRevTo->push(headRevTo->top());
						headRevTo = headRevTo->pop();
					}
					if (copied == head->size()) {
						head = tailRevTo;
						tailRevFrom = nullptr;
						tailRevTo = nullptr;
						headRevFrom = nullptr;
						headRevTo = nullptr;
						copied = 0;
						break;
					}
				}
			}
		}
		
		return make_shared<PQueue<T>>(head, tail, tailRevFrom, tailRevTo, headRevFrom, headRevTo, copied);
	}

	shared_ptr<PQueue<T>> create(shared_ptr<PStack<T>> head, shared_ptr<PStack<T>> tail,
		shared_ptr<PStack<T>> tailRevFrom, shared_ptr<PStack<T>> tailRevTo,
		shared_ptr<PStack<T>> headRevFrom, shared_ptr<PStack<T>> headRevTo, int copied) {
		bool init = tailRevFrom.get() == nullptr;

		if (tail->size() > head->size()) {
			if (tail->size() == 1) {
				head = tail;
				tail = PStack<T>::empty();
			} else {
				// initiate the transfer process
				tailRevFrom = tail;
				tailRevTo = PStack<T>::empty();
				headRevFrom = head;
				headRevTo = PStack<T>::empty();

				tail = PStack<T>::empty();
			}
		}

		int steps = init && tailRevFrom.get() != nullptr ? 4 : 3;
		return step(head, tail, tailRevFrom, tailRevTo, headRevFrom, headRevTo, copied, steps);
	}
	
	static shared_ptr<PQueue<T>> empty() {
		static shared_ptr<PQueue<T>> ptr = make_shared<PQueue<T>>();
		return ptr;
	}
};

const int MAXOPT = 1000005;

shared_ptr<PQueue<int>> vers[MAXOPT];

int main() {
	vers[0] = PQueue<int>::empty();

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
			shared_ptr<PQueue<int>> ptr(vers[ver]);
			int size = ptr->size();
			for (int i = 0; i < size && i < 3; i++) {
				printf("<%d", ptr->front());
				ptr = ptr->pop();
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
