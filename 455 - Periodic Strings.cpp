#include<stdio.h>
#include<string.h>
#define MaxL 1000
int KMP_init(char *A) {
	int i, j;
	int P[MaxL];
	P[0] = -1, i = 1, j = -1;
	while(A[i]) {
		while(j >= 0 && A[j+1] != A[i])
			j = P[j];
		if(A[j+1] == A[i])
			++j;
		P[i] = j, ++i;
	}
	return j;
}
int main() {
	int T;
	char s[MaxL];
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s);
		int l = strlen(s), t = KMP_init(s);
		if(l%(l-t-1))
			printf("%d\n", l);
		else
			printf("%d\n", l-t-1);
		if(T)	puts("");
	}
    return 0;
}
