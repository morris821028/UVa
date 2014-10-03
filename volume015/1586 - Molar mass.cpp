#include <stdio.h>
#include <string.h>
int main() {
	int testcase;
	char s[1024];
	double gmol[128];
	gmol['C'] = 12.01;
	gmol['H'] = 1.008;
	gmol['O'] = 16.00;
	gmol['N'] = 14.01;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		double ret = 0; 
		int n = strlen(s);
		for (int i = 0; i < n; ) {
			int ele = s[i], num = 0;
			i++;
			while (s[i] >= '0' && s[i] <= '9')
				num = num * 10 + s[i] - '0', i++;
			if (num == 0)
				num = 1;
			ret += gmol[ele] * num;
		}
		printf("%.3lf\n", ret);
	}
	return 0;
}
