#include <stdio.h>
int addDay[] = {0, 0, 31, 59, 90, 120, 151,
                181, 212, 243, 273, 304,
                334, 365};
int mDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int cntDay(int y, int m, int d) {
    int sum, leap, isleap;
    isleap = (y%4 == 0 && y%100 != 0) || y%400 == 0;
    y--;
    leap = y/4 - y/100 + y/400;
    sum = y*365 + leap + addDay[m] + (m > 2)*isleap + d;
    return sum;
}
int main() {
    int y, m, d, base;
    int q;
    while (scanf("%d %d", &y, &base) == 2) {
    	scanf("%d", &q);
    	while (q--) {
    		scanf("%d %d", &m, &d);
    		if (m < 1 || m > 12) {
    			puts("-1");
    			continue;
    		}
    		int isleap;
    		isleap = (y%4 == 0 && y%100 != 0) || y%400 == 0;
    		if (d < 1 || d > mDay[m] + (m == 2 && isleap)) {
    			puts("-2");
    			continue;
    		}
    		int diff = cntDay(y, m, d) - cntDay(y, 1, 1);
    		diff = (diff + base)%7;
    		printf("%d\n", diff);
    	}
    }
    return 0;
}

