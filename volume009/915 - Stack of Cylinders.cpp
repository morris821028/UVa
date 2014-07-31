#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int n, cases = 0;
	while(scanf("%d", &n) == 1) {
		if(cases++)	puts("");
		double radius[128], posX[128];
		for(int i = 1; i <= n; i++)
			scanf("%lf", &radius[i]);
			
		double mx = 0;
		int prev[128] = {}, tail = 0;
		for(int i = 1; i <= n; i++) {
			double x = radius[i];
			for(int j = 1; j < i; j++) {
				double nx = sqrt(pow(radius[i]+radius[j], 2) - pow(radius[i]-radius[j], 2)) + posX[j];
				if(nx > x) 
					prev[i] = j;
				x = max(x, nx);
//				printf("sqrt = %lf\n", pow(radius[i]+radius[j], 2) - pow(radius[i]-radius[j], 2));
			}
//			printf("prev[%d] %d\n", i, prev[i]);
			posX[i] = x;
			if(posX[i] + radius[i] > mx)
				tail = i;
			mx = max(mx, posX[i] + radius[i]);
		}
		printf("%.1lf\n", mx);
		vector<int> ret;
		while(tail) {
			ret.push_back(tail);
			tail = prev[tail];
		}
		printf("%d\n", ret.size());
		for(int i = ret.size() - 1; i >= 0; i--)
			printf("%d\n", ret[i]);
	}
	return 0;
}
/*
7
3
25
35
5
4
32
4
*/
