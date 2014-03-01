#include<stdio.h>
int main() {
	int F[45] = {1,2}, T, N, i;
	for(i = 2; i < 45; i++)
		F[i] = F[i-1] + F[i-2];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		i = 44;
		while(F[i] > N)	i--;
		for(; i >= 0; i--) {
			if(F[i] <= N)
				printf("1"), N -= F[i];
			else
				printf("0");
		}
		puts("");
	}
    return 0;
}
