#include<stdio.h>
#include<stdlib.h>
int Calu(int n) {
	int sum = 0;
	while(n) {
		sum += n%10;
		n /= 10;
	}
	return sum;
}
int main() {
	int Y, M, D, n, i, MM, SS;
	while(scanf("%d %d %d", &Y, &M, &D) == 3) {
		MM = Calu(Y)+Calu(M)+Calu(D);
		while(MM >= 10)
			MM = Calu(MM);
		scanf("%d", &n);
		int Idx, min = 10;
		for(i = 1; i <= n; i++) {
			scanf("%d %d %d", &Y, &M, &D);
			SS = Calu(Y)+Calu(M)+Calu(D);
			while(SS >= 10)
				SS = Calu(SS);
			if(abs(SS-MM) < min)
				min = abs(SS-MM), Idx = i;
		}
		printf("%d\n", Idx);
	}
	return 0;
}
