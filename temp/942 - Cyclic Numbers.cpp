#include <stdio.h> 
#include <map>
using namespace std;
#define MAXN 1048576
char buf[MAXN];
int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		printf("%d", n/m);
		map<int, int> R;
		int t = 0, back = -1;
		printf(".");
		n %= m;
		R[n] = -1;
		for (int i = 0; n; i++, t++) {
			buf[i] = (n * 10)/m + '0';
			n = (n * 10)%m;
			if (R.count(n))	{
				buf[i+1] = n * 10 / m + '0';
				back = R[n] + 1, t++;
				break;
			}
			R[n] = i;
		}
		if (t == 0) {
			t++, buf[0] = '0';
		} 
		for (int i = 0; i < t; i++) {
			if (i == back && n)
				printf("(");
			putchar(buf[i]);
		}
		if (back != -1 && n)	
			printf(")");
		puts("");
	}
	return 0;
}
