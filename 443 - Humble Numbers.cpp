#include<stdio.h>
int main() {
	int DP[5842] = {1}, t2 = 0, t3 = 0, t5 = 0, t7 = 0;
	int tmp, i;
	for(i = 1; i < 5842; i++) {
		while(DP[t2]*2 <= DP[i-1])	t2++;
		while(DP[t3]*3 <= DP[i-1])	t3++;
		while(DP[t5]*5 <= DP[i-1])	t5++;
		while(DP[t7]*7 <= DP[i-1])	t7++;
		tmp = DP[t2]*2;
		if(DP[t3]*3 < tmp)	tmp = DP[t3]*3;
		if(DP[t5]*5 < tmp)	tmp = DP[t5]*5;
		if(DP[t7]*7 < tmp)	tmp = DP[t7]*7;
		DP[i] = tmp;
	}
	int n;
	while(scanf("%d", &n) == 1 && n) {
		printf("The %d", n);
		if(n%10 == 1 && n%100 != 11)
			printf("st");
		else if(n%10 == 2 && n%100 != 12)
			printf("nd");
		else if(n%10 == 3 && n%100 != 13)
			printf("rd");
		else
			printf("th");
		printf(" humble number is %d.\n", DP[n-1]);
	}
	return 0;
}
