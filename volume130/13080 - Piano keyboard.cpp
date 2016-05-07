#include <bits/stdc++.h>
using namespace std;

const char s[][16] = {
	"Dob", "Do", "Do#", "Reb", "Re", "Re#", "Mib", "Mi", "Fab", 
	"Mi#", "Fa", "Fa#", "Solb", "Sol", "Sol#", "Lab", "La",
	"La#", "Sib", "Si", "Si#"};
const int w[] = {
	-1, 0, 1, 1, 2, 3, 3, 4, 4,
	5, 5, 6, 6, 7, 8, 8, 9,
	10, 10, 11, 12};
int main() {
	int m = sizeof(s) / sizeof(s[0]);
	map<string, int> R;
	for (int i = 1; i <= 7; i++) {
		int base = i * 12;
		for (int j = 0; j < m; j++) {
			char buf[16];
			sprintf(buf, "%s%d", s[j], i);
//			printf("%s %d\n", buf, base + w[j]);
			R[buf] = base + w[j];
		}
	}
	int n;
	while (scanf("%d", &n) == 1 && n) {
		map<int, int> ret;
		for (int i = 0; i < n; i++) {
			char buf[16];
			scanf("%s", buf);
			ret[R[buf]]++;
//			printf("%s %d\n", buf, R[buf]);
		}
		int prev = -1;
		for (auto &e : ret) {
			if (prev == -1) {
				printf("%d", e.second), prev = e.first+1;
			} else {
				for (; prev < e.first; prev++)
					printf(" 0");
				printf(" %d", e.second), prev = e.first+1;
			}
		}
		puts("");
	}
	return 0;
}
/*
9
Mi#1 Mib1 Fa#1 Fab1 Mi1 Mib1 Fab1 La#1 Lab1
*/

