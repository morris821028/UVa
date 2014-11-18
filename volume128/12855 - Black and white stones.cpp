#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	long long A, B;
	char s[8192];
	while (scanf("%lld %lld", &A, &B) == 2) {
		scanf("%s", s);
		B = A - B;
		int n = strlen(s);
		long long ret = 0;	
		long long inv = 0, w = 0, b = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == 'W')	w++;
			else				inv += w;
		}
		int fw = 0, fb = n;
		for (int i = 0; i < n; i++)
			if (s[i] == 'W')	fw = i, i = n;
		for (int i = n-1; i >= 0; i--)
			if (s[i] == 'B')	fb = i, i = -1;
		w = b = 0;
		for (int i = fw; i <= fb; i++)
			if (s[i] == 'W')	w++;
			else				b++;
		while (inv) {
			if ((w + b - 1) * B <= A) {
				ret += inv * B;
				inv = 0;
			} else {
				ret += A;
//				swap(s[fw], s[fb]);
				inv -= w + b - 1, w--, b--;
				fw++, fb--;
				while (fw <= fb && s[fw] != 'W')	fw++, b--;
				while (fb >= fw && s[fb] != 'B')	fb--, w--;
			}
		}
		printf("%lld\n", ret);
	} 
	return 0;
}
/*
2 1
BWWB
5 3
WBWWBWBWBWBBBWWBBB
1000000 0
W
5 5
BWBWBWBWBBWBWBWB
24 22
BWWWWBWWWWWBWWBBBBWBWBWWBWBWW
*/
