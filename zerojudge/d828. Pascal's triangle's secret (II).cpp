#include<stdio.h>
void Mod(int *N) {
	if(*N > 50000) (*N)%=10000;
}
main() {
	int N;
	while(scanf("%d", &N) == 1) {
		if(N < 2)	puts("1");
		else {
			int a=1, b=1, c=1, d=0;
			int A=1, B=0, C=0, D=1, t1, t2, t3, t4;

			while(N) {
				if(N&1) {
					t1 = A*a + B*c;
					t2 = A*b + B*d;
					t3 = C*a + D*c;
					t4 = C*b + D*d;
					A = t1, B = t2, C = t3, D = t4;
					Mod(&A), Mod(&B), Mod(&C), Mod(&D);
				}
				N /= 2;
				t1 = a*a + b*c;
				t2 = a*b + b*d;
				t3 = a*c + c*d;
				t4 = b*c + d*d;
				a = t1, b = t2, c = t3, d = t4;
				Mod(&a), Mod(&b), Mod(&c), Mod(&d);
			}
			printf("%d\n", A%10000);
		}
	}
	return 0;
}
/*a b
  c d*/
