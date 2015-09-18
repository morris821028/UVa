#include <stdio.h>
void print(int y, int m, int base) {
	int mDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int isleap;
	isleap = (y%4 == 0 && y%100 != 0) || y%400 == 0;
	if (isleap)	mDay[2]++;
 	if (m < 1 || m > 12 || base < 0 || base > 6) {
		puts("invalid");
		return ;
	}
		
	puts(" Su Mo Tu We Th Fr Sa");
	puts("=====================");
	for (int i = 0; i < base; i++)
		printf("   ");
	for (int i = 1; i <= mDay[m]; i++) {
		printf("%3d", i);
		if ((i+base)%7 == 0)	puts("");
	}
	if ((mDay[m]+base)%7)	puts("");
	puts("=====================");
}
int main() {
    int y, m, base;
    while (scanf("%d %d %d", &y, &m, &base) == 3) {
    	print(y, m, base);
    }
    return 0;
}


