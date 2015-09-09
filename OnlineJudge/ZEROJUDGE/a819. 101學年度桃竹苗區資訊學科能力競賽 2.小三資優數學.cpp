#include <bits/stdc++.h>
using namespace std;

int n, m;
char s[16];
int main() {
	scanf("%d", &n);
	scanf("%s", s);
	scanf("%d", &m);
	int x;
	sscanf(s, "%d", &x);
	if (x == m)
		printf("%d\n", m);
	for (int op = 0; op < 4; op++) {
		for (int i = 0; i < n-1; i++) {
			double a, b;
			char t = s[i+1];
			s[i+1] = '\0';
			sscanf(s, "%lf", &a);
			s[i+1] = t;
			sscanf(s+i+1, "%lf", &b);
			if (op == 0 && a+b == m)
				printf("%.0lf+%.0lf\n", a, b);
			if (op == 1 && a-b == m)
				printf("%.0lf-%.0lf\n", a, b);
			if (op == 2 && a*b == m)
				printf("%.0lf*%.0lf\n", a, b);
			if (op == 3 && b && a/b == m)
				printf("%.0lf/%.0lf\n", a, b);
		} 
	}
	for (int op = 0; op < 4; op++) {
		for (int op2 = 0; op2 < 4; op2++) {
			for (int i = 0; i < n-1; i++) {
				for (int j = i+1; j < n-1; j++) {
					double a, b, c;
					char t = s[i+1];
					s[i+1] = '\0';
					sscanf(s, "%lf", &a);
					s[i+1] = t;
					t = s[j+1], s[j+1] = '\0';
					sscanf(s+i+1, "%lf", &b);
					s[j+1] = t;
					sscanf(s+j+1, "%lf", &c);
					if (op == 0 && op2 == 0 && a+b+c == m)
						printf("%.0lf+%.0lf+%.0lf\n", a, b, c);
					if (op == 0 && op2 == 1 && a+b-c == m)
						printf("%.0lf+%.0lf-%.0lf\n", a, b, c);
					if (op == 0 && op2 == 2 && a+b*c == m)
						printf("%.0lf+%.0lf*%.0lf\n", a, b, c);
					if (op == 0 && op2 == 3 && c && a+b/c == m)
						printf("%.0lf+%.0lf/%.0lf\n", a, b, c);
					if (op == 1 && op2 == 0 && a-b+c == m)
						printf("%.0lf-%.0lf+%.0lf\n", a, b, c);
					if (op == 1 && op2 == 1 && a-b-c == m)
						printf("%.0lf-%.0lf-%.0lf\n", a, b, c);
					if (op == 1 && op2 == 2 && a-b*c == m)
						printf("%.0lf-%.0lf*%.0lf\n", a, b, c);
					if (op == 1 && op2 == 3 && c && a-b/c == m)
						printf("%.0lf-%.0lf/%.0lf\n", a, b, c);
					if (op == 2 && op2 == 0 && a*b+c == m)
						printf("%.0lf*%.0lf+%.0lf\n", a, b, c);
					if (op == 2 && op2 == 1 && a*b-c == m)
						printf("%.0lf*%.0lf-%.0lf\n", a, b, c);
					if (op == 2 && op2 == 2 && a*b*c == m)
						printf("%.0lf*%.0lf*%.0lf\n", a, b, c);
					if (op == 2 && op2 == 3 && c && a*b/c == m)
						printf("%.0lf*%.0lf/%.0lf\n", a, b, c);
					if (op == 3 && op2 == 0 && b && a/b+c == m)
						printf("%.0lf/%.0lf+%.0lf\n", a, b, c);
					if (op == 3 && op2 == 1 && b && a/b-c == m)
						printf("%.0lf/%.0lf-%.0lf\n", a, b, c);
					if (op == 3 && op2 == 2 && b && a/b*c == m)
						printf("%.0lf/%.0lf*%.0lf\n", a, b, c);
					if (op == 3 && op2 == 3 && b && c && a/b/c == m)
						printf("%.0lf/%.0lf/%.0lf\n", a, b, c);
				}				
			}
		}

	}
	return 0;
}

/*
3
123
4

3
234
14

7
4822241
1
*/
