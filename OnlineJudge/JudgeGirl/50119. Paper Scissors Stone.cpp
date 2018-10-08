#include <stdio.h>

int main() {
	int x0, a, b, c;
	int y0, d, e, f;
	int n;
	scanf("%d %d %d %d", &x0, &a, &b, &c);
	scanf("%d %d %d %d", &y0, &d, &e, &f);
	scanf("%d", &n);
	char tb[][3] = {
		{2, 0, 1},
		{1, 2, 0},
		{0, 1, 2}
	};
	for (int i = 0; i < n; i++) {
		char v;
		int r = 1;
		for (r = 1; ; r++) {
			v = tb[x0%3][y0%3];
			x0 = (a*x0+b)%c, y0 = (d*y0+e)%f;
			if (v != 2)
				goto DONE;	
		}
		DONE:
		if (v == 1)
			printf("0 %d\n", r);
		else
			printf("1 %d\n", r);
	}
	return 0;
}
