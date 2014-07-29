#include <stdio.h> 
#include <algorithm>
using namespace std;

int main() {
	int n, a, b;
	int v[1024];
	while(scanf("%d", &n) == 1 && n) {
		scanf("%d %d", &a, &b);
		
		int mx = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d", &v[i]);
			v[i] *= 6; // v[i]/3, v[i]/2, v[i]/1
			mx = max(mx, v[i]);
		}
		
		int minCost = 0x3f3f3f3f;
		for(int i = 0; i < n; i++)  {
			for(int j = 1; j <= 3; j++) {
				int S = v[i]/j;
				int x = 0, y = 0;
				
				if(S * 3 < mx)	continue;
				
				for(int k = 0; k < n; k++) {
					x += (S * (v[k]/S + (v[k]%S != 0)) - v[k]);
					y += v[k]/S + (v[k]%S != 0);
				}
				if(a * x + 6 * b * y < minCost)
					minCost = a * x + 6 * b * y;
			}
		}
		if(minCost%6 == 0)
			printf("%d\n", minCost /6);
		else {
			int div = 6, g = __gcd(minCost, div);
			div /= g, minCost /= g;
			printf("%d / %d\n", minCost, div);
		}
	}
	return 0;
}
