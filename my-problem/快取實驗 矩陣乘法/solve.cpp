#include <bits/stdc++.h>
using namespace std;

#define LOOP_UNROLL 8
class Matrix {
public:
	vector< vector<int> > data;
	int row, col;
	Matrix(int n = 1, int m = 1) {
		row = n, col = m;
		data = vector< vector<int> >(n, vector<int>(m, 0));
	}
	void rand_gen(int c) {
		int x = 2, n = row * col;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				x = ((long long) x * x + c + i + j)%n;
				data[i][j] = x;
			}
		}
	}
	unsigned long multiply(Matrix &x) {
		x.transpose();
		unsigned long h = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < x.col; j++) {
				register int sum = 0;
				int *a = &data[i][0], *b = &x.data[j][0], k;
				for (k = 0; k+LOOP_UNROLL < col; k += LOOP_UNROLL) {
					sum += *a * *b, a++, b++;
					sum += *a * *b, a++, b++;
					sum += *a * *b, a++, b++;
					sum += *a * *b, a++, b++;
					sum += *a * *b, a++, b++;
					sum += *a * *b, a++, b++;
					sum += *a * *b, a++, b++;
					sum += *a * *b, a++, b++;
				}
				for (; k < col; k++)
					sum += *a * *b, a++, b++;
				h = hash(h + sum);
			}
		}
		return h;
	}
	void transpose() {
		for (int i = 0; i < row; i++)
        	for (int j = i+1; j < col; j++)
            	swap(data[i][j], data[j][i]);
	}
	void print() {
		for (int i = 0; i < row; i++) {
			printf("[");
			for (int j = 0; j < col; j++)
				printf(" %d", data[i][j]);
			printf(" ]\n");
		}
	}
private:
	unsigned long hash(unsigned long x) {
		return (x * 2654435761LU);
	}
} A(1000, 1000), B(1000, 1000);
int main() {
	int N, S1, S2;
	while (scanf("%d %d %d", &N, &S1, &S2) == 3) {
		A.row = A.col = B.row = B.col = N;
		A.rand_gen(S1);
		B.rand_gen(S2);
		printf("%lu\n", A.multiply(B));
	}
	return 0;
}

