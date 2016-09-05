#include <stdio.h>
int n;
int da, db, dc, ea, eb, ec, fa, fb, fc;
int solve(int a, int b, int c) {
	if (a == 0 && b == 0 && c == 0)
		return 1;
	if (a < 0 || b < 0 || c < 0)
		return 0;
	return solve(a - da, b - db, c - dc) ||
		solve(a - ea, b - eb, c - ec) ||
		solve(a - fa, b - fb, c - fc);
}
void query(int n) {
	if (n == 0)
		return ;
	int a, b, c, ret;
	scanf("%d %d %d", &a, &b, &c);
	ret = solve(a, b, c);
	puts(ret ? "yes" : "no");
	query(n-1);
}
int main() {
	scanf("%d %d %d", &da, &db, &dc);
	scanf("%d %d %d", &ea, &eb, &ec);
	scanf("%d %d %d", &fa, &fb, &fc);
	scanf("%d", &n);
	query(n);
	return 0;
}

