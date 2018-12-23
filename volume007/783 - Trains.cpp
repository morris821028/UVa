#include <bits/stdc++.h>
using namespace std;

int main() {
	int d, t1, v1, t2, v2, tf;
	while (scanf("%d %d %d %d %d %d", &d, &v1, &v2, &t1, &t2, &tf) == 6) {
		int ret = 0;
		for (int i = 0; i <= tf; i += t1) {
			double p_tl = i, p_tr = min(i + (double) d/v1, (double) tf);
			for (int j = 0; j <= tf; j += t2) {
				double q_tl = j, q_tr = min(j + (double) d/v2, (double) tf);
				if (max(p_tl, q_tl) <= min(p_tr, q_tr)) {
					if (p_tl <= q_tl) {
						double t = q_tl + (d - (q_tl-p_tl)*v1)/(double) (v1+v2);
						if (t <= q_tr && t <= p_tr) {
							ret++;
						}
					} else {
						double t = p_tl + (d - (p_tl-q_tl)*v2)/(double) (v1+v2);
						if (t <= q_tr && t <= p_tr) {
							ret++;
						}
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
10 5 5 1 1 2 
20 5 7 2 3 200
*/
