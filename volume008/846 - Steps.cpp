#include <stdio.h>
#include <math.h>
int main() {
	int t, x, y, L;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &x, &y);
		L = y-x;
		int steps = 0, n = (int)sqrt(L);
		steps = n;
		L -= n*(n+1)/2;
		while(L > 0) {
			while(n*(n+1)/2 > L)	
				n--;
			if(n*(n+1)/2 == L)
				L = 0, steps += n;
			else
				L -= n, steps ++;
		}
		printf("%d\n", steps);
	}
    return 0;
}
