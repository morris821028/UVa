#include <stdio.h>
#include <algorithm>
using namespace std;

int n, m, a[524288];
int main() {
	while(scanf("%d %d", &n, &m) == 2 && n >= 0) {
		int l = 1, r = 0, mid;
		for(int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			r = max(r, a[i]);
		}
		int ret = r;
		while(l <= r) {
			mid = (l + r)/2;
			int box = 0;
			for(int i = 0; i < n; i++)
				box += a[i]/mid + (a[i]%mid != 0);
			if(box <= m)
				r = mid - 1, ret = mid;
			else
				l = mid + 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
