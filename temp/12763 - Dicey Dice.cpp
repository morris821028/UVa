#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase;
	char s[10];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int player = s[0] - 'A';
		int dice[3][6];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				scanf("%d", &dice[i][j]);
			}
		}
		double rmx = 0, rmx2 = 1;
		for (int i = 0; i < 3; i++) { // A player pick
			double mx = 1, mx2 = 0;
			for (int j = 0; j < 3; j++) { // B player pick
				if (i == j)	continue;
				int pa = 0, pb = 0;
				for (int p = 0; p < 6; p++) {
					for (int q = 0; q < 6; q++) {
						pa += dice[i][p] > dice[j][q];
						pb += dice[i][p] < dice[j][q];
					}
				}
				
				if (mx > pa / 36.0 || (mx == pa / 36.0 && mx2 < pb/36.0)) {
					mx = pa /36.0;
					mx2 = pb / 36.0;
				}
			}
			if (rmx < mx || (rmx == mx && rmx2 > mx2)) {
				rmx = mx;
				rmx2 = mx2;
			}
		}
		if (rmx > rmx2)
			printf("%c\n", player + 'A');
		else if (rmx < rmx2)
			printf("%c\n", 1 - player + 'A');
		else
			printf("fair\n");
//			printf("%lf %lf\n", rmx, rmx2);
	}
	return 0;
}
/*
3
A
1 1 1 1 1 1
2 3 2 4 5 3
6 6 6 6 6 6
A
4 3 7 9 2 5
8 1 4 6 9 2
6 5 1 8 3 7
B
1 2 3 4 4 4
1 2 3 4 4 4
1 2 3 4 4 4
*/
