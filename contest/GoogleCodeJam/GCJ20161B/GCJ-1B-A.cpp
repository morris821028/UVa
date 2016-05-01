#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
const char ES[][16] = {"ZERO", "ONE", "TWO", "THREE", "FOUR",
        "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
class GAUSSIAN { // Gaussian Elimination
public:
    static const int MAXN = 16;
    double mtx[MAXN][MAXN+1], var[MAXN];
    int exist[MAXN], n;
	GAUSSIAN() {
		memset(mtx, 0, sizeof(mtx));
	}
    void compute(int n, int m) {
        const double eps = 1e-12;
        this->n = n;
		/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= m; j++) {
				printf("%.2lf ", mtx[i][j]);
			}
			puts("");
		}
		puts("--");
		*/
		for (int i = 0, c; i < n; i++) {
			c = i;
			for (int j = i; j < n; j++)
				if (fabs(mtx[c][i]) < fabs(mtx[j][i]))
					c = j;
			if (fabs(mtx[c][i]) < eps)
				continue;
			if (c != i) {
				for (int j = 0; j <= m; j++)
					swap(mtx[c][j], mtx[i][j]);
			}
			for (int j = 0; j < n; j++) {
				if (i == j) continue;
				for (int k = m; k >= i; k--) {
					mtx[j][k] -= mtx[j][i]/mtx[i][i]*mtx[i][k];
				}
			}
		}
		/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= m; j++) {
				printf("%.2lf ", mtx[i][j]);
			}
			puts("");
		}
		puts("--");
		*/
		for (int i = 0; i < m; i++)
			exist[i] = 1;
		for (int i = m-1; i >= 0; i--) {
			if (fabs(mtx[i][i]) < eps) {
				exist[i] = 0;
				continue;
			}
			if (fabs(mtx[i][m]) < eps)
				var[i] = 0;
			else
				var[i] = mtx[i][m]/mtx[i][i];
			for (int j = i+1; j < m; j++)
				if (fabs(mtx[i][j]) > eps && exist[j])
					exist[i] = 0;
		}
		for (int i = 0; i < m; i++) {
			int cnt = round(var[i]);
			for (int j = 0; j < cnt; j++)
				printf("%d", i);
		}
		puts("");
	}
};
int main() {
	int R[128] = {}, rsize = 0;
	memset(R, -1, sizeof(R));
	for (int i = 0; i < 10; i++) {
		for (int j = 0; ES[i][j]; j++) {
			if (R[ES[i][j]] == -1)
				R[ES[i][j]] = rsize++;
		}
	}

	double f[32][32] = {};
	for (int i = 0; i < 10; i++) {
		for (int j = 0; ES[i][j]; j++) {
			f[R[ES[i][j]]][i]++;
		}
	}

	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		char S[2048];
		GAUSSIAN g;
		scanf("%s", S);
		for (int i = 0; i < rsize; i++) {
			for (int j = 0; j < 10; j++) {
				g.mtx[i][j] = f[i][j];
			}
		}
		for (int i = 0; S[i]; i++) 
			g.mtx[R[S[i]]][10]++;
		printf("Case #%d: ", ++cases);
		g.compute(rsize, 10);
	}

	return 0;
}
