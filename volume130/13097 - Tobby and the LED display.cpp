#include <bits/stdc++.h>
using namespace std;
int main() {
	int N;
	long long T;
	static char buf[3][262144], dirS[1024];
	while (scanf("%d %lld", &N, &T) == 2) {
		T %= N;
		scanf("%s", dirS);
		while (getchar() != '\n');
		for (int i = 0; i < 3; i++)
			fgets(buf[i], 262144, stdin);
		fputs(buf[0], stdout);
		int pos = dirS[0] == 'R' ? N - T : N + T;
		pos = (pos + N)%N;
		pos = pos * 2;
		for (int i = pos; i < 2*N; i++)
			putchar(buf[1][i]);
		for (int i = 0; i <= pos; i++)
			putchar(buf[1][i]);
		puts("");
		fputs(buf[2], stdout);
	}
	return 0;
}

