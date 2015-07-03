#include <bits/stdc++.h> 
using namespace std;

int main() {
	int n, m;
	char s[1024];
	while (scanf("%d %d", &n, &m) == 2) {
		bitset<512> attr[n];
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			attr[i] = bitset<512>(s);
		}
		
		double ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				int a = (attr[i]&attr[j]).count();
				int b = (attr[i]|attr[j]).count();
				if (5 * a >= 4 * b)
					ret++;
			}
		}
		printf("%.2lf\n", ret * 100 / (n * (n-1)/2));
	}
	return 0;
}
/*
8 10
1101011110
1101011110
0101011110
1101011110
1111101101
1000101110
1000001110
1001101110
*/
