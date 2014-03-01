#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char x[1000001], y[1000001];
int s[2][1000001];
void binary_gcd(int in1, int in2, int s1, int s2) {
	int flag = 0, a;
	if(in1 == in2) { /*s1 s2 change  to (s1 > s2)*/
		for(a = 0; a <= in1; a++)
			if(s[s1][a] > s[s2][a]) {flag = 2; break;}
			else if(s[s1][a] < s[s2][a]) {flag = 1; break;}
		if(flag == 1) {
			int t;
			t = s1, s1 = s2, s2 = t;
		}
	}
	if(in1 < in2)  {
		int t;
		t = s1, s1 = s2, s2 = t;
		t = in1, in1 = in2, in2 = t;
	}
	if(in2 == -1) {
		a = 0;
		while(s[s1][a] == 0) a++;
		for(; a <= in1; a++) putchar(s[s1][a] + '0');
		return ;
	}
	if(in1 == in2 && flag == 0) { /*s1 == s2*/
		a = 0;
		while(s[s1][a] == 0) a++;
		for(; a <= in1; a++) putchar(s[s1][a] + '0');
		return ;
	}
	else if(s[s1][in1] == 0 && s[s2][in2] == 0) {
		binary_gcd(in1-1, in2-1, s1, s2), putchar('0');
	}
	else if(s[s1][in1] == 0 && s[s2][in2] == 1) {
		binary_gcd(in1-1, in2, s1, s2);
	}
	else if(s[s1][in1] == 1 && s[s2][in2] == 0) {
		binary_gcd(in1, in2-1, s1, s2);
	}
	else { /*s1-s2 s2*/
		int b;
		s[s1][in1] ++;
		for(a = in1, b = in2; a >=0 && b >=0; a--, b--) {
			s[s1][a] += ! s[s2][b];
			if(s[s1][a] > 1 && a != 0) {
				s[s1][a-1] += s[s1][a]/2;
				s[s1][a] %= 2;
			}
		}
		while(a >= 0) {
			s[s1][a] ++;
			if(s[s1][a] > 1 && a != 0) {
				s[s1][a-1] += s[s1][a]/2;
				s[s1][a] %= 2;
			}
			a--;
		}
		s[s1][0] %= 2;
		binary_gcd(in1, in2, s1, s2);
	}
}
main() {
	while(scanf("%s %s", x, y) == 2) {
		int a, l = strlen(x);
		for(a = 0; a < l; a++) s[0][a] = x[a] - '0';
		l = strlen(y);
		for(a = 0; a < l; a++) s[1][a] = y[a] - '0';
		binary_gcd(strlen(x)-1, strlen(y)-1, 0, 1), puts("");
	}
	return 0;
}
