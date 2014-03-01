#include<stdio.h>
main() {
	int L, R;
	while(scanf("%d %d", &L, &R) == 2) {
		int Ans = 0, t;
		for(; L <= R; L++) {
			t = L; 
			while(t) { 
				Ans += (t%10 == 2); 
				t /= 10; 
			} 
		} 
		printf("%d\n", Ans); 
	}
	return 0;
}
