#include <bits/stdc++.h>

template<typename T>
struct PStack {
	T elem;	
	PStack<T> *next;
	int size;

	PStack(): size(0), elem(), next(nullptr) {}
	PStack(T elem, PStack<T> *next, int size):
		size(size), elem(elem), next(next) {}
	
	T top() const {
		return elem;	
	}

	PStack<T>* push(T elem) {
		return new PStack(elem, this, size + 1);
	}

	PStack<T>* pop() const {
		return next != nullptr ? next : PStack<T>::emptyStack();
	}

	static PStack<T>* emptyStack() {
		static PStack<T> *empty = nullptr;
		if (empty == nullptr)
			empty = new PStack();
		return empty;
	}
	
	PStack(const PStack&) = delete;
    PStack& operator= (const PStack) = delete;
};

const int MAXOPT = 1000005;

PStack<int> *vers[MAXOPT];

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
class Print {
public:
    static const int N = 1048576;
    char buf[N], *p, *end;
    Print() {
        p = buf, end = buf + N - 1;
    }
    void print(char c) {
    	if (p == end) {
            *p = '\0';
            printf("%s", buf), p = buf;
        }
    	 *p = c, p++;
	}
    void printInt(int x, char padding) {
        static char stk[16];
        int idx = 0;
        int neg = x < 0;
        x = abs(x);
        stk[idx++] = padding;
        if (!x)	
            stk[idx++] = '0';
        while (x)
            stk[idx++] = x%10 + '0', x /= 10;
        if (neg)
        	stk[idx++] = '-';
        while (idx) {
            if (p == end) {
                *p = '\0';
                printf("%s", buf), p = buf;
            }
            *p = stk[--idx], p++;
        }
    }
    ~Print() {
        *p = '\0';
        printf("%s", buf);
    }
} bprint;

int main() {
	vers[0] = PStack<int>::emptyStack();

	int cmd, v, x;
	int ver = 0;
//	while (scanf("%d", &cmd) == 1) {
	while (ReadInt(&cmd)) {
		ver++;
		if (cmd == 0) {
//			scanf("%d", &v);
			ReadInt(&v);
			vers[ver] = vers[v];
		} else if (cmd == 1) {
//			scanf("%d", &x);
			ReadInt(&x);
			vers[ver] = vers[ver-1]->push(x);
		} else if (cmd == 2) {
			vers[ver] = vers[ver-1]->pop();
		} else {
			vers[ver] = vers[ver-1];
			PStack<int> *ptr = vers[ver];
			int size = ptr->size;
			for (int i = 0; i < size && i < 3; i++) {
//				printf("%d ", ptr->top());
				bprint.printInt(ptr->top(), ' ');
				ptr = ptr->pop();
			}
			if (size > 3)
//				printf("... ");
				bprint.print('.'), bprint.print('.'), bprint.print('.'), bprint.print(' ');
//			puts("]");
			bprint.print(']'), bprint.print('\n');
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
