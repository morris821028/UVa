#include <stdio.h>
#include <algorithm>
using namespace std;
// greedy, math
const int MAXN = 100005;
double pos[MAXN], D;
int main() {
	int n, cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf", &pos[i]);
		scanf("%lf", &D);
		
		sort(pos, pos + n);
		double t = 0;
		for (int i = 1; i < n; i++) {
			if (pos[i] - pos[i-1] > D) { // at t-time, i-th object must move left
				if ((pos[i] - t) - pos[i-1] > D) { // late
					double move = ((pos[i] - t) - pos[i-1] - D)/2;
					pos[i] = pos[i] - move - t; // move: move left to be heated, t: greedy move left, at t-time.
					t += move;
				} else {
					pos[i] = pos[i-1] + D;
				}
			} else { // i-th object move right
				if (pos[i] + t < pos[i-1] + D)
					pos[i] = pos[i] + t;
				else
					pos[i] = pos[i-1] + D;
			}
		}
		printf("Case %d: %.3lf\n", ++cases, t);
	}	 
	return 0;
}
