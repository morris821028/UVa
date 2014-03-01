#include<stdio.h>
main() {
	long long n, p, i;
	while(scanf("%lld", &n) == 1)  {
		p = 1, i = 1; 
		while(1) {
			if(i&1) p *= 9; 
			else p *= 2;
			if(p >= n) {
				if(i&1) 
					puts("Stan wins."); 
				else
					puts("Ollie wins."); 
				break; 
			}
			i++; 
		} 
	} 
	return 0; 
}
/*
這題的解法就是在 n = 1 - 9 時為史丹贏、n = 10 - 18 為歐力贏、
n = 19 - 162 為史丹贏、n = 163 - 324 為歐力贏....。
也就是說，當史丹決定乘數時，p 用 9 乘，看它有沒有大於 n，
如果有大於 n，就是史丹贏；當為歐力決定乘數時，p 用 2 乘，
看它有沒有大於 n，如果有大於 n，就是歐力贏。
*/ 
