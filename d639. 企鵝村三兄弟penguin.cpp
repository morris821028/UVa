#include<stdio.h>
typedef struct {
	int t[3][3];
}Matrix;
Matrix in, I3, o, init;
Matrix mult(Matrix x, Matrix  y) {
	Matrix t = o;
	int i, j, k;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			for(k = 0; k < 3; k++) {
				t.t[i][k] += x.t[i][j]*y.t[j][k] %10007;
				t.t[i][k] %= 10007;
			}
	return t;
}
void ans(int n) {
	Matrix x = init, y = in;
	while(n) {
		if(n&1) x = mult(x, y);
		y = mult(y, y);
		n /= 2;
	}
	printf("%d\n", x.t[0][0]);
}
main() {
	int n, a, b;
	for(a = 0; a < 3; a++)
		for(b = 0; b < 3; b++)
			in.t[a][b] = 0, I3.t[a][b] = 0,
			o.t[a][b] = 0, init.t[a][b] = 0;
	for(a = 0; a < 3; a++) I3.t[a][a] = 1;
	init.t[0][0] = 5;
	init.t[1][0] = init.t[0][1] = 3;
	init.t[0][2] = init.t[1][1] = init.t[1][2] = 1;
	init.t[2][0] = init.t[2][1] = init.t[2][2] = 1;
	in.t[0][0] = in.t[0][1] = 1;
	in.t[1][0] = in.t[1][2] = 1;
	in.t[2][0] = 1;
	while(scanf("%d", &n) == 1) {
		if(n <= 3) puts("1");
		else if(n == 4) puts("3");
		else ans(n-5);
	}
	return 0;
}
