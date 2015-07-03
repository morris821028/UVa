#include <bits/stdc++.h> 
using namespace std;

const double threshold = 0.8;
char s[1024][1024];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
		
		double ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				int a = 0, b = 0;
				for (int k = 0; k < m; k++) {
					a += s[i][k] == '1' && s[j][k] == '1';
					b += s[i][k] == '1' || s[j][k] == '1';
				}
				if (a * 5 >= 4 * b)
					ret++;
			}
		}
		printf("%.2lf\n", ret * 100 / (n * (n-1)/2));
	}
	return 0;
}
/*
8 10
0111101101
0111101100
0111101100
0111101101
1100101010
0111101100
0111101100
0011101111
*/
