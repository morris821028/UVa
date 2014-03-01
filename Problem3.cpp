#include<stdlib.h>   
#include<stdio.h>
int Calu(int n) {
	int t = 10, i;
	for(i = 1; ; i++) { 
		if(n < t)	return i;
		t *= 10;
	} 
}
main() {
	int a, b, i, j, x;
	int Map[11][11] = {0};
	for(i = 1; i < 10; i++) {
		Map[i][0] = 1;
		for(j = 1; j < 10; j++) 
			Map[i][j] = Map[i][j-1]*i;
	}
	while(scanf("%d %d", &a, &b) == 2) {
		if(a > b)	x = a, a = b, b = x;
		int Ans[10000], At = 0, tmp, dnn;
		for(i = a; i <= b; i++) {
			j = i, tmp = 0, dnn = Calu(j);
			while(j) {
				tmp += Map[j%10][dnn];
				j /= 10;
			}
			if(tmp == i)
				Ans[At++] = i;
		}
		for(i = 0; i < At-1; i++)
			printf("%d ", Ans[i]);
		if(At > 0)	printf("%d", Ans[i]);
		puts("");
	}
	return 0;   
}
