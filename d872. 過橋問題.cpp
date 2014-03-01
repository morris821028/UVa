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
int Line[1001] = {};
short Index1, Index2;
short Findback() {
	while(1) {
		if(Line[Index1]) {
			Line[Index1] --;
			return Index1;
		}
		else Index1--;
	}
}
short Findnext() {
	while(1) {
		if(Line[Index2]) {
			Line[Index2] --;
			return Index2;
		}
		else Index2++;
	}
}
main() {
	register int N, a;
	while(1) {
		N = Input();
		if(N == EOF) break;
		
		for(a = 0, Index1 = 1000, Index2 = 0; a < N; a++)
			Line[Input()]++;
		register int time = 0;
		register short t1, t2, Min1 = Findnext(), Min2 = Findnext(), Y, Z;
		while(N > 3) {
			Z = Findback(), Y = Findback();
			t1 = Min2 + Min1 + Z + Min2;/*1. AB + A + YZ + B*/
			t2 = Z + Min1 + Y + Min1;/*2. AZ + A + AY + A*/
			time += (t1 < t2)? t1 : t2;
			N -= 2;
		}
		if(N == 2) time += Min2;
		else if(N == 3) time += Min1 + Min2 + Findnext();
		else if(N == 1) time += Min1;
		printf("%d\n", time);
	}
	return 0;
}
