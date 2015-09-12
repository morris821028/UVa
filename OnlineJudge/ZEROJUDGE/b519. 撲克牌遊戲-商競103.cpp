#include <bits/stdc++.h>
using namespace std;

int scorePoker(int cards[]) {
	for (int i = 0; i < 5; i++)
		cards[i]--;
	int m[4][13] = {};
	for (int i = 0; i < 5; i++)
		m[cards[i]/13][cards[i]%13] = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			int ok = 1;
			for (int k = 0; k < 5; k++)
				ok &= m[i][(j+k)%13];
			if (ok)
				return 7;
		}
	}
	for (int i = 0; i < 13; i++) {
		int ok = 0;
		for (int j = 0; j < 4; j++)
			ok += m[j][i];
		if (ok == 4)
			return 6;
	}
	for (int i = 0; i < 13; i++) {
		for (int j = i+1; j < 13; j++) {
			int p1 = 0, p2 = 0;
			for (int k = 0; k < 4; k++)
				p1 += m[k][i], p2 += m[k][j];
			if (p1 == 3 && p2 == 2)
				return 5;
			if (p1 == 2 && p2 == 3)
				return 5;
			if (p1 == 2 && p2 == 2)
				return 2;
		}
	}
	for (int i = 0; i < 10; i++) {
		int ok = 1;
		for (int j = 0; j < 5; j++) {
			int has = 0;
			for (int k = 0; k < 4; k++) 
				has |= m[k][(i+j)%13];
			ok &= has;
		}
		if (ok)
			return 4;
	}
	for (int i = 0; i < 13; i++) {
		int p1 = 0;
		for (int j = 0; j < 4; j++)
			p1 += m[j][i];
		if (p1 == 3)
			return 3;
		if (p1 == 2)
			return 1;
	}
	return 0;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int cards[5];
		for (int i = 0; i < 5; i++)
			scanf("%d", &cards[i]);
		printf("%d\n", scorePoker(cards));
	}
	return 0;
}