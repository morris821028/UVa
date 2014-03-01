#include<stdio.h>
int cmd[1000], x[1000];
int testStack(int n) {
	int Stack[1005], idx = -1;
	int i;
	for(i = 0; i < n; i++) {
		if(cmd[i] == 1) {
			Stack[++idx] = x[i];
		} else {
			if(idx < 0 || Stack[idx] != x[i])
				return 0;
			--idx;
		}
	}
	return 1;
}
int testQueue(int n) {
	int Queue[1005], head = 0, tail = -1;
	int i;
	for(i = 0; i < n; i++) {
		if(cmd[i] == 1)
			Queue[++tail] = x[i];
		else {
			if(head > tail || Queue[head] != x[i])
				return 0;
			++head;
		}
	}
	return 1;
}
int testPriorityQueue(int n) {
	int Heap[1005], L = 0, P, S, tmp; /*max-heap*/
	int i;
	for(i = 0; i < n; i++) {
		if(cmd[i] == 1) {
			Heap[++L] = x[i];
			S = L, P = S>>1;
			while(S >= 2 && Heap[S] > Heap[P]) {
				tmp = Heap[S], Heap[S] = Heap[P], Heap[P] = tmp;
				S = P, P = S>>1;
			}
		} else {
			if(L < 1 || Heap[1] != x[i])
				return 0;
			tmp = Heap[L], Heap[L] = Heap[1], Heap[1] = tmp;
			P = 1, S = P<<1, --L;
			while(S <= L) {
				if(S < L && Heap[S+1] > Heap[S])
					S++;
				if(Heap[S] <= Heap[P])
					break;
				tmp = Heap[S], Heap[S] = Heap[P], Heap[P] = tmp;
				P = S, S = P<<1;
			}
		}
	}
	return 1;
}
int main() {
	int n, i;
	while(scanf("%d", &n) == 1) {
		for(i = 0; i < n; i++)
			scanf("%d %d", &cmd[i], &x[i]);
		int flag = 0, ans;
		if(testStack(n))	
			ans = 1, flag++;
		if(testQueue(n))	
			ans = 2, flag++;
		if(testPriorityQueue(n))	
			ans = 3, flag++;
		if(flag == 0)
			puts("impossible");
		else if(flag == 1) {
			if(ans == 1)
				puts("stack");
			else if(ans == 2)
				puts("queue");
			else
				puts("priority queue");
		} else {
			puts("not sure");
		}
	}
    return 0;
}
