#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#define Done 1
typedef struct Node {
	int length, width;
	int state, next;
};
Node node[32768*50];
int size;
int A[20], n, x, y, i;
int Link[32768], Sqrt[10001];
int LOG2[32768], Sum[32768];
char Used[101], mark[32768][101], times;
int check(int length, int width) {
	if(length <= x && width <= y)
		return 1;
	if(length <= y && width <= x)
		return 1;
	return 0;
}
void insertList(int state, int length, int width) {
	if(check(length, width) == 0)	return;
	if(mark[state][length] != 0)	return;
	static int prev, curr;
	prev = 0, curr = Link[state];
	while(curr != 0) {
		if(node[curr].length < length)	break;
		else if(node[curr].length == length)
			return;
		else
			prev = curr, curr = node[curr].next;
	}
	size++;
	if(prev == 0)	Link[state] = size;
	else			node[prev].next = size;
	node[size].length = length;
	node[size].width = width;
	node[size].state = state;
	node[size].next = curr;
	mark[state][length] = width;
	mark[state][width] = length;
	if(Used[length])
		Used[length]--, times--;
	if(Used[width])
		Used[width]--, times--;
}
void doCombine(int state1, int state2) {
	static int i, j, state;
	static int a, b, c, d;
	state = state1 | state2;
	for(i = Link[state1]; i; i = node[i].next) {
		a = node[i].length, b = node[i].width;
		if(mark[state2][a] != 0) {
			insertList(state, a, b+mark[state2][a]);
			insertList(state, b+mark[state2][a], a);
		}
		if(mark[state2][b] != 0) {
			insertList(state, b, a+mark[state2][b]);
			insertList(state, a+mark[state2][b], b);
		}
		if(times == 0)	return;
	}
}
void doBuild() {
	int i, maxState, minState;
	int state, state1, state2;
	int s, finalState, sqr, tmp;
	finalState = (1<<n)-1;
	for(state = 1; state <= finalState; state++) {
		s = LOG2[state&(-state)];
		maxState = (state>>s)-1;
		minState = 1;
		Sum[state] = Sum[state-(state&(-state))]+Sum[state&(-state)];
		sqr = Sqrt[Sum[state]], tmp = Sum[state], times = 0;
		memset(Used, 0, sizeof(Used));
		for(i = 1; i <= sqr; i++)
			if(tmp%i == 0 && check(i, tmp/i) == 1) {
				Used[i]++, Used[tmp/i]++;
				times += 2;
			}
		for(i = minState; i <= maxState; i++) {
			if((state&(i<<s)) == (i<<s)) {
				state1 = i<<s;
				state2 = state ^ state1;
				if(state1 > state2)	break;
				doCombine(state1, state2);
				if(times == 0)		break;
			}
		}
	}
	if(mark[finalState][x] != 0)
		puts("Yes");
	else
		puts("No");
}
int initBuild() {
	int i, j, sqr, finalState;
	size = 0, finalState = (1<<n)-1;
	for(i = 0; i <= finalState; i++)
		Link[i] = 0, memset(mark[i], 0, sizeof(mark[i]));
	for(i = 0; i < n; i++) {
		sqr = Sqrt[A[i]];
		for(j = 1; j <= sqr; j++) {
			if(A[i]%j == 0 && check(j, A[i]/j) == 1) {
				insertList(1<<i, j, A[i]/j);
				insertList(1<<i, A[i]/j, j);
			}
		}
		Sum[1<<i] = A[i];
	}
} 
int main() {
	int Case = 0, tmp, i;
	for(i = 0; i <= 32767; i++)
		LOG2[i] = (int)log2(i);
	for(i = 0; i <= 10000; i++)
		Sqrt[i] = (int)sqrt(i);
	while(scanf("%d", &n) == 1 && n) {
		scanf("%d %d", &x, &y);
		int sum = 0;
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]), sum += A[i];
		printf("Case %d: ", ++Case);
		if(sum != x*y) {
			puts("No");
			continue;
		}
		initBuild();
		doBuild();
		
	}
    return 0;
}
