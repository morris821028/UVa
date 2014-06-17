#include <stdio.h>
#include <stdlib.h>
int Calu(int n, int k) {
	static int link[101], i, j, head, prev, last;
	for(i = 2; i < n; i++)
		link[i] = i+1;
	link[n] = 2, head = 2, prev = n;
	for(i = 1; i < n; i++) {
		for(j = 1; j < k; j++)
			prev = head, head = link[head];
		last = head;
		link[prev] = link[head];
		head = link[head];
	}
	if(last == 13)		return 1;
	return 0;
}
int main() {
	int D[100], N, count, i;
	for(i = 14; i < 100; i++) {
		count = 2;
		while(Calu(i, count) == 0)	count++;
		D[i] = count;
	}
	D[13] = 1;
	while(scanf("%d", &N) == 1 && N) {
		printf("%d\n", D[N]);
	}
    return 0;
}
