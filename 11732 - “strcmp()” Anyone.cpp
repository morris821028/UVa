#include<stdio.h>
#include<string.h>
char str[4000][1002];
struct {
	int st, ed;
}Range1[8000], Range2[8000], *RA, *RB, *RT;
long long solve(int n) {
	RA = Range1, RB = Range2;
	int i, j, k, Rt = 1, RBt, tRBt;
	long long Ans = 0;
	int S0[8000], S1[8000], *A, *B, *T, asci[128], tmp, tn;
	RA[0].st = 0, RA[0].ed = n-1;
	A = S0, B = S1;
	for(i = 0; i < n; i++)		S0[i] = i;
	for(i = 0; ; i++) {
		if(Rt == 0)	break;
		RBt = 0;
		for(k = 0; k < Rt; k++) {
			tRBt = RBt;
			if(RA[k].st >= RA[k].ed || (i > 0 && str[A[RA[k].st]][i-1] == '\0'))	continue;
			memset(asci, 0, sizeof(asci));
			for(j = RA[k].st; j <= RA[k].ed; j++)
				asci[str[A[j]][i]]++;
			for(j = 1; j < 128; j++)	asci[j] += asci[j-1];
			for(j = RA[k].ed; j >= RA[k].st; j--)
				B[--asci[str[A[j]][i]]+RA[k].st] = A[j];
			int start = RA[k].st;
			/*printf("<");
			for(j = RA[k].st; j <= RA[k].ed; j++) {
				printf("%c", str[B[j]][i]);
			}
			printf(">");*/
			for(j = RA[k].st+1; j <= RA[k].ed; j++) {
				if(str[B[j]][i] == str[B[j-1]][i])	continue;
				else {
					RB[RBt].st = start, RB[RBt].ed = j-1;
					start = j;
					RBt++;
				}
			}
			RB[RBt].st = start, RB[RBt].ed = j-1;
			RBt++;
			for(j = tRBt, tmp = 0, tn; j < RBt; j++) {
				tn = RB[j].ed - RB[j].st + 1;
				Ans += tn*(tn-1);
				Ans += tn*tmp;
				tmp += tn;
			}
		}
/*		puts("");*/
		T = A, A = B, B = T;
		RT = RA, RA = RB, RB = RT;
		Rt = RBt;
	}
	return Ans;
}
int main() {
	int N, C = 0, i, k = 0;
	while(scanf("%d", &N) == 1 && N) {
		getchar();
		for(i = 0; i < N; i++)		scanf("%s", str[i]);
		printf("Case %d: %lld\n", ++C, solve(N));
	}
    return 0;
}
/*
7
aaaa
aaaa
aaaa
aaaa
aaaa
aaaa
aaaa
*/

