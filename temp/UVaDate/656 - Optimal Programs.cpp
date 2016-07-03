#include <stdio.h> 
#include <string.h>
#include <stack>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

const char opName[5][8] = {"ADD","DIV","DUP","MUL","SUB"};
enum ACTION {ADD, DIV, DUP, MUL, SUB};
struct Seq {
	vector<int> op;
	int dup;
};
int N, X[16], Y[16];

int validate(const vector<int> &seq) {
	stack<int> STK[16];
	for (int i = 0; i < N; i++)
		STK[i].push(X[i]);
	for (int i = 0; i < seq.size(); i++) {
		for (int j = 0; j < N; j++) {
			stack<int> &stk = STK[j];
			switch(seq[i]) {
				case DIV:
					if (stk.top() == 0)	return -1;
			}
			switch(seq[i]) {
				case ADD: case SUB: case MUL: case DIV:
					if (stk.size() < 2)	return -1;
			}
			int a, b;
			switch(seq[i]) {
				case ADD:
					a = stk.top(), stk.pop();
					b = stk.top(), stk.pop();
					stk.push(b+a);
					break;
				case SUB:
					a = stk.top(), stk.pop();
					b = stk.top(), stk.pop();
					stk.push(b-a);
					break;
				case MUL:
					a = stk.top(), stk.pop();
					b = stk.top(), stk.pop();
					stk.push(b*a);
					break;
				case DIV:
					a = stk.top(), stk.pop();
					b = stk.top(), stk.pop();
					stk.push(b/a);
					break;
				case DUP:
					stk.push(stk.top());
					break;
			}
			if (abs(stk.top()) > 30000)
				return -1;
		}
	}
	int same = 1;
	for (int i = 0; i < N && same; i++)
		same &= STK[i].top() == Y[i] && STK[i].size() == 1;
	return same;
}
void bfs() {
	int same = 1;
	for (int i = 0; i < N; i++)
		same &= X[i] == Y[i];
	if (same) {
		puts("Empty sequence");
		return ;
	}
	
	queue<Seq> Q;
	Seq u, v;
	Q.push(Seq());
	while (!Q.empty()) {
		u = Q.front(), Q.pop();			
		if (u.op.size()%2 == 0 && u.dup == u.op.size()/2) {
			int f = validate(u.op);
			if (f == 1) {
				for (int i = 0; i < u.op.size(); i++)
					printf("%s%c", opName[u.op[i]], i == u.op.size()-1 ? '\n' : ' ');
				return ;
			}
		}
		for (int i = 0; i < 5; i++) {
			v = u;
			v.op.push_back(i), v.dup = u.dup + (i == DUP);
			if (v.op.size() > 10)
				continue;
			if (v.dup >= v.op.size() - v.dup)
				Q.push(v);
		}
	}
	puts("Impossible");
}
int main() {
	int cases = 0;
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 0; i < N; i++)
			scanf("%d", &X[i]);
		for (int i = 0; i < N; i++)
			scanf("%d", &Y[i]);
		
		printf("Program %d\n", ++cases);
		
		bfs();
		puts("");
	}
	return 0;
}
/*
4
1 2 3 4
0 -2 -6 -12
1
30000
-30000
3
1 2 3
1 11 1998
1
1998
1998
0
*/
