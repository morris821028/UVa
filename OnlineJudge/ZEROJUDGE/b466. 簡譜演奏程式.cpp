#include <bits/stdc++.h>
using namespace std;
const double ff[] = {0, 261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88};
const double pi = acos(-1);
int main() {
	char s[1024];
	int F, T, R, N, slen;
	scanf("%s", s);
	slen = strlen(s);
	R = 8000, N = R * slen * 0.25; 
	printf("%d %d\n", R, N);
	for (int i = 0, pp = 0; s[i]; i++) {
		if (s[i] == '-')
			s[i] = s[i-1];
		else
			pp = 0;
		double d = ff[s[i] - '0'] * 2 * pi / R;
		for (int j = 0; j < R / 4; j++, pp++) {
			int f = round(32767 * sin((double)pp * d));
			printf("%d ", f);
		}
	}
	puts("");
	return 0;
}
