#include<stdio.h>
int main() {
    double a, b;
    int INF = 2147483647;
    char op, s[2000];
    while(gets(s)) {
		printf("%s\n", s);
		sscanf(s, "%lf %c %lf", &a, &op, &b);
		if(a > INF)
			puts("first number too big");
		if(b > INF)
			puts("second number too big");
		if(op == '+' && a+b > INF)
			puts("result too big");
		if(op == '*' && a*b > INF)
			puts("result too big");
    }
    return 0;
}
