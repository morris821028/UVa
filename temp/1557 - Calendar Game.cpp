#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

const int mday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int dp[128][16][32], used[128][16][32], dcases = 0;
int validDate(int yyyy, int mm, int dd) {
	if (mm < 1 || mm > 12)	
		return 0;
	if ((yyyy%4 == 0 && yyyy%100 != 0) || (yyyy%400) == 0) {
		if (mm == 2) {
			if (dd < 1 || dd > 29)	
				return 0;
		} else {
			if (dd < 1 || dd > mday[mm])
				return 0;
		}			
	} else {
		if (dd < 1 || dd > mday[mm])
			return 0;
	}
	return 1;
}
int complete(int yyyy, int mm, int dd) {
	return yyyy == 2001 && mm == 11 && dd == 4;
}
int fail(int yyyy, int mm, int dd) {
	if (!validDate(yyyy, mm, dd))
		return 1;
	if (yyyy > 2001)	return 1;
	if (yyyy < 2001)	return 0;
	if (mm > 11)		return 1;
	if (mm < 11)		return 0;
	if (dd > 4)			return 1;
	if (dd < 4)			return 0;
	return 0;
}
void nextMonth(int &yyyy, int &mm, int &dd) {
	mm++;
	if (mm == 13)	yyyy++, mm = 1;
}
void nextDay(int &yyyy, int &mm, int &dd) {
	int mday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((yyyy%4 == 0 && yyyy%100 != 0) || (yyyy%400) == 0)
		mday[2] = 29;
	dd++;
	if (dd > mday[mm])
		mm++, dd = 1;
	if (mm == 13)	yyyy++, mm = 1;
}
int dfs(int yyyy, int mm, int dd) {
	if (fail(yyyy, mm, dd))
		return 0;
	if (complete(yyyy, mm, dd))
		return 1;
	if (used[yyyy-1900][mm][dd] == dcases)
		return dp[yyyy-1900][mm][dd];
	int &ret = dp[yyyy-1900][mm][dd];
	int y, m ,d;	
	ret = 0, used[yyyy-1900][mm][dd] = dcases;
	
	y = yyyy, m = mm, d = dd;
	nextMonth(y, m, d);
	if (complete(y, m, d))
		ret = 1;
	if (!fail(y, m, d))
		ret |= !dfs(y, m, d);
	
	y = yyyy, m = mm, d = dd;
	nextDay(y, m, d);
	if (complete(y, m, d))
		ret = 1;
	if (!fail(y, m, d))
		ret |= !dfs(y, m, d);
	return ret;
}
int main() {
	int testcase;
	int yyyy, mm, dd;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &yyyy, &mm, &dd);
		dcases ++;
		printf("%s\n", dfs(yyyy, mm, dd) ? "YES" : "NO");
	}
	return 0;
}
/*
3
2001 11 3
2001 11 2
2001 10 3
*/
