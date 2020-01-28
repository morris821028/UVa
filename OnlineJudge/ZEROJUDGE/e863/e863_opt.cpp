#include <bits/stdc++.h>

template<typename T>
struct PStack {
	T elem;	
	PStack<T> *next;
	int sz;

	PStack(): sz(0), elem(), next(nullptr) {}
	PStack(T elem, PStack<T> *next, int sz):
		sz(sz), elem(elem), next(next) {}
	
	T top() const {
		return elem;	
	}

	PStack<T>* push(T elem) {
		return new PStack(elem, this, sz + 1);
	}

	PStack<T>* pop() const {
		return next != nullptr ? next : PStack<T>::emptyStack();
	}

	int size() {
		return sz;
	}

	static PStack<T>* emptyStack() {
		static PStack<T> *empty = new PStack();
		return empty;
	}
	
	PStack(const PStack&) = delete;
    PStack& operator= (const PStack) = delete;
};

template<typename T> class PQueue;
template<typename T> class TQueue;

template<typename T>
class PQueue {
protected:
	PStack<T> *head;
	PStack<T> *tail;
public:	
	PQueue(): PQueue(PStack<T>::emptyStack(), PStack<T>::emptyStack()) {}
	PQueue(PStack<T> *head, PStack<T> *tail):
		head(head), tail(tail) {}

	static PQueue<T>* emptyQueue() {
		static PQueue<T> *empty = new PQueue();
		return empty;
	}
	
	virtual int size() {
		return head->size() + tail->size();
	}

	T front() {
		return head->top();
	}

	virtual PQueue<T>* push(T elem) {
		return create(head, tail->push(elem));
	}

	virtual PQueue<T>* pop() {
		if (size() == 1)
			return emptyQueue();
		return create(head->pop(), tail);
	}

	PQueue(const PQueue&) = delete;
    PQueue& operator= (const PQueue) = delete;

	PQueue<T>* step(PStack<T> *head, PStack<T> *tail, PStack<T> *tailRevFrom, PStack<T> *tailRevTo,
		PStack<T> *headRevFrom, PStack<T> *headRevTo, int copied, int cost) {
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
						return new PQueue<T>(head, tail);
					}
				}
			}
		}
		if (tailRevFrom != nullptr) {
			return new TQueue<T>(head, tail, tailRevFrom, tailRevTo, headRevFrom, headRevTo, copied);
		}
		return new PQueue<T>(head, tail);
	}

	PQueue<T>* create(PStack<T> *head, PStack<T> *tail) {
		if (tail->size() > head->size()) {
			if (tail->size() == 1) {
				head = tail;
				tail = PStack<T>::emptyStack();
			} else {
				// initiate the transfer process
				PStack<T> *tailRevFrom = tail;
				PStack<T> *tailRevTo = PStack<T>::emptyStack();
				PStack<T> *headRevFrom = head;
				PStack<T> *headRevTo = PStack<T>::emptyStack();

				tail = PStack<T>::emptyStack();
				return step(head, tail, tailRevFrom, tailRevTo, headRevFrom, headRevTo, 0, 4);
			}
		}
		return new PQueue<T>(head, tail);
	}
};

template<typename T>
class TQueue : public PQueue<T> {
private:
	PStack<T> *tailRevFrom;
	PStack<T> *tailRevTo;
	PStack<T> *headRevFrom;
	PStack<T> *headRevTo;
	int copied;
public:
	TQueue(PStack<T> *head, PStack<T> *tail, PStack<T> *tailRevFrom, PStack<T> *tailRevTo,
		PStack<T> *headRevFrom, PStack<T> *headRevTo, int copied):
		PQueue<T>(head, tail), tailRevFrom(tailRevFrom), tailRevTo(tailRevTo),
		headRevFrom(headRevFrom), headRevTo(headRevTo), copied(copied) {}
	
	int size() override {
		int sz = PQueue<T>::size();
		return sz + tailRevTo->size() + tailRevFrom->size() - copied;
	}

	PQueue<T>* push(T elem) override {
		return create(PQueue<T>::head, PQueue<T>::tail->push(elem), tailRevFrom, tailRevTo,
			headRevFrom, headRevTo, copied);
	}

	PQueue<T>* pop() override {
		if (size() == 1)
			return PQueue<T>::emptyQueue();
		return create(PQueue<T>::head->pop(), PQueue<T>::tail, tailRevFrom, tailRevTo,
			headRevFrom, headRevTo, copied);
	}

	TQueue(const TQueue&) = delete;
    TQueue& operator= (const TQueue) = delete;

	PQueue<T>* create(PStack<T> *head, PStack<T> *tail, PStack<T> *tailRevFrom, PStack<T> *tailRevTo,
		PStack<T> *headRevFrom, PStack<T> *headRevTo, int copied) {
		if (tail->size() > head->size()) {
			if (tail->size() == 1) {
				head = tail;
				tail = PStack<T>::emptyStack();
			} else {
				// initiate the transfer process
				tailRevFrom = tail;
				tailRevTo = PStack<T>::emptyStack();
				headRevFrom = head;
				headRevTo = PStack<T>::emptyStack();

				tail = PStack<T>::emptyStack();
			}
		}

		return PQueue<T>::step(head, tail, tailRevFrom, tailRevTo, headRevFrom, headRevTo, copied, 3);
	}
};

const int MAXOPT = 1000005;

PQueue<int> *vers[MAXOPT];

int main() {
	vers[0] = PQueue<int>::emptyQueue();

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
			PQueue<int> *ptr = vers[ver];
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
