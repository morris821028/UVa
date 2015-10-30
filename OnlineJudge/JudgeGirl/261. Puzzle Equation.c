#include <stdio.h>
#include <string.h>
#include <ctype.h>
char s[3][64];
int slen[3];
int A[26], Aval[26], R[26], An;
int C[64];
int dfs(int idx) {
	if (idx == An) {
		int val[3] = {};
		for (int i = 0; i < 3; i++) {
			for (int j = slen[i]-1; j >= 0; j--) {
				if (isalpha(s[i][j]))
					val[i] = val[i] * 10 + Aval[R[s[i][j] - 'A']];
				else
					val[i] = val[i] * 10 + s[i][j] - '0';
			}
		}
		if (val[0] * val[1] == val[2]) {
			char split[3][16] = {" x ", " = ", "\n"};
			for (int i = 0; i < 3; i++) {
				for (int j = slen[i]-1; j >= 0; j--) {
					if (isalpha(s[i][j]))
						printf("%d", Aval[R[s[i][j] - 'A']]);
					else
						printf("%c", s[i][j]);
				}
				printf("%s", split[i]);
			}
			return 1;
		}
		return 0;
	}
	for (int i = 0; i < 10; i++) {
		Aval[idx] = i;
		if (dfs(idx+1))
			return 1;
	}
	return 0;
}
int main() {
	scanf("%s %s %s", s[0], s[1], s[2]);
	for (int i = 0; i < 3; i++) {
		slen[i] = strlen(s[i]);
		for (int j = 0, k = slen[i]-1; j < k; j++, k--) {
			char t;
			t = s[i][j], s[i][j] = s[i][k], s[i][k] = t;
		}
	}
	memset(R, -1, sizeof(R));
	memset(C, 0, sizeof(C));
	An = 0;
	for (int i = 0; i < slen[0] || i < slen[1] || i < slen[2]; i++) {
		for (int j = 0; j < 3; j++) {
			if (i >= slen[j])	continue;
			if (isalpha(s[j][i])) {
				if (R[s[j][i] - 'A'] == -1) {
					A[An++] = s[j][i] - 'A';
					R[s[j][i] - 'A'] = An-1;
				}
			}
		}
	}
	int f = dfs(0);
	return 0;
}
