#include<stdio.h>
#include<stdlib.h>
#define MaxV 2147483647
typedef struct {
	int arrive, v, in;
}Work;
Work Data[1001]; 
int cmp(const void *a, const void *b) {
	Work *aa, *bb;
	aa = (Work *)a, bb = (Work *)b;
	if(aa->arrive > bb->arrive)			return 1;
	else if(aa->arrive < bb->arrive)	return 0;
	else {
		return aa->in > bb->in;
	}
}
main() {
	int n, a, b, C = 0;
	while(scanf("%d", &n) == 1) {
		C++;
		int machine[21], ar, v, in = 0;
		for(a = 1; a <= n; a++)
			scanf("%d", &machine[a]);
		while(scanf("%d %d", &ar, &v) == 2) {
			if(ar == 0 && v == 0) break;
			Data[in].arrive = ar, Data[in].v = v;
			Data[in].in = in, in++;
		}
		qsort(Data, in, sizeof(Work), cmp);
		int worktime[21] = {};
		for(a = 0; a < in; a++) {
			int min_mach = 0, t, min;
			double tx, min2 = MaxV;
			for(b = 1; b <= n; b++) {
				if(worktime[b] == 0 || worktime[b] < Data[a].arrive)
					t = Data[a].arrive;
				else	t = worktime[b];
				tx = t*60 + 5*60 + ((double)Data[a].v*60)/machine[b];
				tx = (int)(tx + (tx > (int)tx));
				t += 5 + Data[a].v/machine[b] + (Data[a].v%machine[b] != 0) + 10;
				if(tx < min2)	min = t, min_mach = b, min2 = tx;
			}
			worktime[min_mach] = min;
			Data[a].arrive = min - 10 - (Data[a].v/machine[min_mach] + (Data[a].v%machine[min_mach] != 0));
			Data[a].v = min_mach;
		}
		printf("%d %d\n", Data[in-1].arrive, Data[in-1].v);
	}
	puts("OLE");
	return 0;
}
