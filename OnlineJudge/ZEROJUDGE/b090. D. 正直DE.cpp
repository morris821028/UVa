#include<stdio.h>		
long long DP[1002][1002] = {}, A[1002];
long long MAX = 0x7fffffffffffffffLL, temp, m;
int Input() { 
    char cha; 
    unsigned int x = 0; 
    while(cha = getchar()) 
        if(cha != ' ' && cha != '\n' || cha == EOF) break; 
    if(cha == EOF) return -1;
    x = cha-48; 
    while(cha = getchar()) { 
        if(cha == ' ' || cha == '\n') break; 
        x = x*10 + cha-48; 
    } 
    return x; 
}
main() {
	int n, t, a, b, c, d;
	long long total = 0, Ans;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(a = 0; a < n; a++)
			A[a] = Input(), A[a+1] = Input();
			DP[a][a] = 0;
		for(a = 1; a < n; a++) {
			for(b= 0, c= a + b; c < n; b++, c++) {
				m = MAX;
				for(d = b; d < c; d++) {
					temp = DP[b][d] + DP[d+1][c] + A[b]*A[d+1]*A[c+1];
					if(m > temp) m = temp;
				}
				DP[b][c] = m;
			}
		}
		Ans = DP[0][n-1];
		printf("%lld\n", (Ans-1)/1000+1);
		total += Ans;
	}
	printf("%lld\n", (total-1)/1000+1);
	return 0;
}
