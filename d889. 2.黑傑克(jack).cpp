#include<stdio.h>
int next(int mark[]) {
	static int index = 0; 
	while(1) {
		if(mark[index]) {
			mark[index]--; 
			return index; 
		} 
		else index++; 
	} 
} 
main() {
	int n, a, x; 
	while(scanf("%d", &n) == 1)  {
		int mark[10001] = {}; 
		for(a = 0; a < n; a++) 
			scanf("%d", &x), mark[x]++; 
		int Ans = 0; 
		for(a = 0; a < n; a++) {
			x = next(mark); 
			if(x > Ans + 29) break; 
			else {
				if(x < Ans) Ans += 5; 
				else Ans = x + 5; 
			} 
		}
		Ans += 30;
		printf("%d\n", Ans); 
	}
	return 0; 
}
