#include<stdio.h>
int main() {
	int n, t, i, tmp;
	int Ans[500] = {1}, At = 28;
	for(i = 0; i <= 27; i++) {
		if(i)
			Ans[i] = Ans[i-1]*2;
		Ans[At] = Ans[i]*5;
		while(Ans[At] <= 100000000)
			t = Ans[At]*5, Ans[++At] = t;
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(i = 1, tmp = 0; i <= At; i++)
			if(Ans[i] <= n)
				tmp++;
		printf("%d\n", tmp);
	}
	return 0;
}
