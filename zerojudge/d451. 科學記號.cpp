#include<stdio.h>
main() {
	int T, d, a, b;
	char s[102];
	scanf("%d", &T);
	while(T--) {
		scanf("%s %d", s, &d);
		int pointset = -1, numflag = 0, numset = 0;
		int S[102] = {}, L = 0;
		for(a = 0; s[a]; a++) {
			if(s[a] >= '0' && s[a] <= '9') {
				S[L] = s[a] - '0';
				if(numflag == 0 && s[a] != '0')
					numset = L, numflag = 1;
				L++;
			}
			if(s[a] == '.')
				pointset = L-1;
		}if(pointset == -1) pointset = L-1;
		
		if(numset+d <= L) {/*¤£¸É0*/
			int index = numset+d-1;			
			if(S[numset+d] >= 5) {
				S[index]++; 
				while(S[index] >= 10 && index >= 1) {
					if(index - 1 >= 0) {
						S[index-1] += S[index]/10, S[index] %= 10; 
					} 
					index--; 
				}
			}
			if(S[index] >= 10) {
				printf("1"); 
			} 
			else { 
				printf("%d", S[numset]);
			} 
			if(d > 1) printf(".");
			
			for(a = numset+1; a < numset+d; a++) 
				printf("%d", S[a]); 
			printf("x10(%d)", (pointset-numset)+(S[index] >= 10));
				
		}
		else {/*¸É0*/ 
			printf("%d", S[numset]); 
			if(d > 1) printf("."); 
			for(a = numset+1; a < numset+d; a++) 
				printf("%d", S[a]); 
			printf("x10(%d)", (pointset-numset));
		}
		puts("");
	}
	return 0;
}
