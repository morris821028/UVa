#include<stdio.h>
#include<stdlib.h>
unsigned short C[1000001] = {};
int Lowbit(int N) {
    return N & (-N);
}
void Modify (int N, int L) {
	while(N <= L) {
    	C[N] += 1;
        N += Lowbit(N);
    }
}
int Operator (int N) {
	int Sum = 0;
    while(N) {
        Sum += C[N];
        N -= Lowbit(N);
	}
	return Sum;
}
int Input() {  
    char cha;  
    unsigned int x = 0;  
    while(cha = getchar())  
        if(cha != ' ' && cha != '\n' || cha == EOF) break;  
    if(cha == EOF) return -1; 
    x = cha-48;  
    while(cha = getchar()) {  
        if(cha == ' ' || cha == '\n') break;  
        x = x*10 + cha-48;  
    }  
    return x;  
}
int binary_search(int k, int l, int h) {
	if(l > h) return -1;
	do {
		int m = (l + h)/ 2, r2 = Operator(m-1), r1 = Operator(m);
		if(r2 > k) h = m - 1;
		else if(r1 < k) l = m + 1;
		else {
			if(r1 == r2) h = m - 1;
			else
				return m;
		}
	}
	while(l <= h);
	return -1;
}
int handle(int x) {
	int r1 = Operator(x), r2 = Operator(x-1);
	if(r1 - r2 > 1) return 0;
	int a, b, min = 1000000;
	a = binary_search(r1 - 1, 1, x-1);
	b = binary_search(r1 + 1, x+1,1000000);
	if(a != -1)	min = x - a;
	if(b != -1) min = (min > b - x) ? b - x : min;
	return min;
}
main() {
    int N, a, x;
	while(scanf("%d", &N) == 1) {
		int Ans = 0;
		x = Input(), Ans = x, Modify(x, 1000000);
		for(a = 1; a < N; a++) {
			x = Input();
			Modify(x, 1000000), Ans += handle(x);
		}
		printf("%d\n", Ans);
	}
    return 0;
}
