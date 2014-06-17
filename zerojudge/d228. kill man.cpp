#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int C[70001] = {}, LOW[70001];
int Modify (int N, int L) {
    while(N <= L) {
        C[N] += 1;
        N += LOW[N];
    }
}
int Operator (int N) {
    int Sum = 0;
    while(N) {
        Sum += C[N];
        N -= LOW[N];
    }
    return Sum;
}
main() { 
	int t, n, m, k, test = 0, a;
	for(a = 0; a < 70001; a++)	LOW[a] = a & (-a);
	scanf("%d",&t);
	while(t--) {
		int a, Ans = 0;
		scanf("%d %d %d", &n, &k, &m);
		memset(C, 0, sizeof(C));
		int kp = 0, skip, lave = n, tk, ttk;
		if(n != m) {
			for(a = 1; a <= m; a++) {
				tk = k%lave;
				if(tk == 0) tk = lave;
				while(tk) {
					if(kp + tk > n) {
						skip = Operator(n) - Operator(kp);
						ttk = tk, tk = tk - (n-kp-skip);
						kp = 0;
					}
					else {
						skip = Operator(kp+tk) - Operator(kp);
						kp = kp + tk;
						tk = skip;
						if(skip == 0) break;
					}
				} 
				Modify(kp, n), lave--;
			}
		} else {
			for(a = 2; a <= n; a++)
				kp = (k+kp)%a;
			kp++;
		}
		printf("Case %d: %d\n", ++test, kp); 
	} 
	return 0;
}
