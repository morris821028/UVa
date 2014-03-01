#include<stdio.h>
#include<stdlib.h>
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
int C[200001]={}, A[200001]={}; 
int lb[200001];
int Modify(int N, int flag) {
	while(N <= 200000) {
		C[N] += flag;
		N += lb[N]; 
	} 
} 
int Operator(int N) {
	int Sum = 0;
	while(N) {
		Sum += C[N];
		N -= lb[N]; 
	} 
	return Sum; 
} 
main() {
	int N, Q, v, L, R, i; 
	int a, b; 

	for(a = 1; a <= 200000; a++) 
		lb[a] = a & -a;
	scanf("%d %d", &N, &Q);
	while(Q--) {
		v = Input(); 
		if(v == 1) {
			i = Input(); 
			if(A[i] == 0) Modify(i, 1);
			else Modify(i, -1); 
		} 
		else {
			L = Input(), R = Input(); 
			b = Operator(R) - Operator(L-1); 
			if(b&1) puts("1");
			else puts("0"); 
		}	
	} 
	return 0; 
}
