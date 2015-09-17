#include <stdio.h>
#include <stdlib.h>
#define swap(x, y) {int t; t = x, x = y, y = t;}
int p[4];
int test(int x) {
	int s = 0;
	for (int k = 3; k >= 0; k--)
		s = s * x + p[k];
	if (s == 0) {
		s = 0;
		for (int k = 3; k >= 0; k--)
			s = s * x + p[k], p[k] = s;
		for (int k = 0; k < 3; k++)
			p[k] = p[k+1];
		p[3] = 0;
		return 1;
	}
	return 0;
}
int main() {
	while (scanf("%d %d %d", &p[2], &p[1], &p[0]) == 3) {
		p[3] = 1;
		int root[3];
		for (int i = 0; i < 3; i++) {
			int n = abs(p[0]), rt;
			for (int j = 0; j*j <= n; j++) {
				if (j == 0 || n%j == 0) {
					if (test(j)) {
						rt = j;
						break;
					} 
					if (test(-j)) {
						rt = -j;
						break;
					}
					if (j) {
						if (test(n/j)) {
							rt = n/j;
							break;
						}
						if (test(-n/j)) {
							rt = -n/j;
							break;
						}
					}
				}
			}
			root[i] = -rt;
		}
		if (root[0] > root[1])	swap(root[0], root[1]);
		if (root[0] > root[2])	swap(root[0], root[2]);
		if (root[1] > root[2])	swap(root[1], root[2]);
		for (int i = 0; i < 3; i++)
			printf("%d%c", root[i], i == 2 ? '\n' : ' ');
	}
	return 0;
}
/*
1 12 47 60
0 -3 -27
1 9 20
*/
