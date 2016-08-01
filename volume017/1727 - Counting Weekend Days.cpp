#include <bits/stdc++.h>
using namespace std;
string day_str[7] = {
	"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};
string mon_str[12] = {
	"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", 
	"AUG", "SEP", "OCT", "NOV", "DEC"
};
int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		char s1[16], s2[16];
		scanf("%s %s", s1, s2);
		int a = find(day_str, day_str+7, s2) - day_str;
		int b = find(mon_str, mon_str+12, s1) - mon_str;
		int ret = 0;
		for (int i = 0; i < days[b]; i++) {
			if ((a + i)%7 == 5 || (a + i)%7 == 6)
				ret++;
		}
		printf("%d\n", ret);
	}
	return 0;
}

