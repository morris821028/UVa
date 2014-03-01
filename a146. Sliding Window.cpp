#include<stdio.h>
int A[1000001], Q[1000001], L[1000001];
int n, k;
void pushmin() {
	int a, head = 1, tail = 0, t;
	for(a = 1; a < k; a++) {
		while(head <= tail && Q[tail] > A[a])
			tail --;
		Q[++tail] = A[a], L[tail] = a;
	}
	for(a = k; a <= n; a++) {
		while(head <= tail && Q[tail] > A[a])
			tail --;
		Q[++tail] = A[a], L[tail] = a;
		t = a - k;
		while(L[head] <= t)	head ++;
		printf("%d%c", Q[head], (a < n) ? ' ' : '\n');
	}
}
void pushmax() {
	int a, head = 1, tail = 0, t;
	for(a = 1; a < k; a++) {
		while(head <= tail && Q[tail] < A[a])
			tail --;
		Q[++tail] = A[a], L[tail] = a;
	}
	for(a = k; a <= n; a++) {
		while(head <= tail && Q[tail] < A[a])
			tail --;
		Q[++tail] = A[a], L[tail] = a;
		t = a - k;
		while(L[head] <= t)	head ++;
		printf("%d%c", Q[head], (a < n) ? ' ' : '\n');
	}
}
int Input() { 
    char cha, flag = 1; 
    unsigned int x = 0; 
    while(cha = getchar()) 
        if(cha != ' ' && cha != '\n' || cha == EOF) break; 
    if(cha != '-')	x = x*10 + cha -48;
    else flag = -1;
    while(cha = getchar()) { 
        if(cha == ' ' || cha == '\n') break; 
        x = x*10 + cha-48; 
    } 
    return x * flag; 
}
main() {
	int a;
	while(scanf("%d %d", &n, &k) == 2) {
		if(k > n) k = n;
		for(a = 1; a <= n; a++)
			A[a] = Input();
		pushmin();
		pushmax();
	}
	return 0;
}
