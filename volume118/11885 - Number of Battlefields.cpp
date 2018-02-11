#include <bits/stdc++.h>
using namespace std;
/*
	reference: UVa 11884 - A Shooting Game
	The blocks are occupying some consecutive columns, and the perimeter 
	of the figure equals the perimeter of its minimal bounding box. To 
	make the battlefield look more exciting, it must not be a perfect 
	rectangle.
	
	If it's a valid battlefield and contains perfect rectangle, 
		satisfy h1 <= h2 <= ... <= hm => ... >= hn-1 >= hn
		
	n: perimeter/2
	a_2 = 1, a_3 = 2
	a_n = 3 a_{n-1} - a_{n-2}
	Explain: 
		(1) +a_{n-1}: add one square into each existed column
		(2) +a_{n-1}: add a new row with one square on the left
		(3) +a_{n-1}: add a new row with one square on the right
		(4) -a_{n-2}: remove duplicate which is intersection of (2) and (3), 
			the height of the leftmost and rightmost is one, add new row with one square.
			
	The number of perfect rectangle is n-1, so the final result is a_n - (n-1).
*/
const int64_t MOD = 987654321LL;
struct Matrix {
	int64_t v[2][2];
	Matrix(int t = 1) {
		memset(v, 0, sizeof(v));
		for (int i = 0; i < 2; i++)
			v[i][i] = t;
	}
	Matrix operator*(const Matrix &y) const {
		Matrix ret(0);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					ret.v[i][j] += v[i][k] * y.v[k][j] % MOD;
					if (ret.v[i][j] >= MOD)
						ret.v[i][j] %= MOD;
				}
			}
		}
		return ret;
	}
	Matrix pow(int y) {
		Matrix ret(1), x = *this;
		while (y) {
			if (y&1)
				ret = ret * x;
			x = x*x, y >>= 1;
		}
		return ret;
	}
};
int main() {
	int p;
	while (scanf("%d", &p) == 1 && p) {
		if ((p&1) || p < 6) {
			puts("0");
			continue;
		}
		int n = p/2;
		Matrix m;
		m.v[0][0] = 3, m.v[0][1] = -1;
		m.v[1][0] = 1, m.v[1][1] = 0;
		Matrix r = m.pow(n-2);
		int64_t ret = r.v[0][0] + r.v[0][1];
		printf("%lld\n", ((ret - (n-1)%MOD)%MOD + MOD)%MOD);
	}
	return 0;
}
