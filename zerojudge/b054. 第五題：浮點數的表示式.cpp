#include<stdio.h>
void change(int n) {
	int a;
	printf(" ");
	for(a = 7; a >= 0; a--)
		printf("%d", (n >> a) &1);
}
main() {
	double n;
	float n2;
	int C = 0;
	unsigned long long * m, * m2;
	while(scanf("%lf", &n) == 1) {
		int a, t1 = 0, t2 = 0, t3 = 0, t4 = 0;

		n2 = (float)n;	
		m = (unsigned long long *) &n;
		for(a = 62; a >= 52; a--)
			t1 |= ((((*m) >> a)&1) << (a-52));
		t1 -= 894;
		t2 = (((*m) >> 63) &1)<<7;
		for(a = 6; a >= 0; a--)
			t2 |= ((((*m) >> (a+45))&1) << a);	
		for(a = 7; a >= 0; a--)
			t3 |= ((((*m) >> (a+37))&1) << a);
		for(a = 7; a >= 0; a--)
			t4 |= ((((*m) >> (a+29))&1) << a);
		printf("Input a value: %g\n", n);
		puts("                 Exponent lst byte 2nd byte 3rd byte");
		printf("Memory Contents=");
		change(t1), change(t2), change(t3), change(t4);
		printf("\n                 <&H%2.2X>   <&H%.2X>   <&H%.2X>   <&H%.2X>\n", t1, t2, t3, t4);
		printf("FLOATING POINT FORMAT =>");
		printf("%s0.1",  (n >= 0) ? " " : " -");
		for(a = 22; a >= 0; a--)
			printf("%d",((*m) >> (a+29))&1);
		printf(" * 2 ^ %d", t1-128);
		printf("\nFloating Point Value = %g\n", n);
		puts("=================================================================");
	}
	return 0;
}
