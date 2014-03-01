#include<stdio.h>
typedef struct {
	int t[2][2];
}Matrix;
Matrix in, I2, o, init;
Matrix mult(Matrix x, Matrix  y) {
	Matrix t = o;
	int i, j, k;
	for(i = 0; i < 2; i++)
		for(j = 0; j < 2; j++)
			for(k = 0; k < 2; k++) {
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
	for(a = 0; a < 2; a++)
		for(b = 0; b < 2; b++)
			in.t[a][b] = 0, I2.t[a][b] = 0,
			o.t[a][b] = 0, init.t[a][b] = 0;
	for(a = 0; a < 2; a++) I2.t[a][a] = 1;
	init.t[0][0] = 1;
	init.t[1][1] = 1;
	in.t[0][0] = in.t[0][1] = 1;
	in.t[1][0] = 1;
	while(scanf("%d", &n) == 1)
		ans(n);
	return 0;
}
