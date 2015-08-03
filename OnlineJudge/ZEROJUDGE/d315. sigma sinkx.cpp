#include <bits/stdc++.h>
using namespace std;
const double pi = 3.1415926;
int main() {
	char s1[1024], s2[1024];
    int n, x;
    while (scanf("%s %s", s1, s2) == 2) {
    	if (!strcmp("0", s1))
    		break;
    	sscanf(s2, "%d", &x);
    	x %= 360;
    	if (x == 0) {
    		puts("0.0000");
    		continue;
    	}
    	n = 0;
    	for (int i = 0; s1[i]; i++)
    		n = (n * 10 + s1[i] - '0')%360;
        double a = x * pi / 180.0 /2;
        double ret = (cos (a) - cos ((2 * n + 1) * a)) / (2 * sin (a));
        printf("%.4lf\n", ret);
    }
    return 0;
} 
