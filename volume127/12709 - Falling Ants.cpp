#include <stdio.h>

int main() {
	for(int n; scanf("%d", &n) == 1 && n;)  {
		int L, W, H, V, maxV, maxH = 0;
		while(n --) {
			scanf("%d %d %d", &L, &W, &H);
			V = L * W * H;
			if(H > maxH || (H == maxH && V > maxV))
				maxH = H, maxV = V;
		} 
		printf("%d\n", maxV);
	}
	return 0;
}
