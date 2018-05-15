#include <bits/stdc++.h>
using namespace std;
// Rabin-Karp Algorithm
int main() {
	static char s[100005], buf[300005], cmd[16];
	const uint32_t hbase = 131;
	int head, tail;
	int q;
	while (head = 100000, scanf("%s", buf+head) == 1) {
		int n = strlen(buf+head);
		tail = head+n-1;
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%s%s", cmd, s);
			if (cmd[0] == '1') {
				buf[--head] = s[0];
			} else if (cmd[0] == '2') {
				buf[++tail] = s[0];
			} else {
				uint32_t h = 0, f = 1;
				n = strlen(s);
				for (int i = 0; i < n; i++)
					h = h*hbase + s[i], f *= hbase;
				uint32_t g = 0;
				int ret = 0;
				for (int i = head; i <= tail; i++) {
					int valid = 1, j = 0;
					for (j = 0; j < n && valid; j++)
						valid &= s[j] == buf[i+j];
					valid &= j == n;
					if (valid) {
//						for (int j = 0; j < n; j++)
//							putchar(buf[i+j]);
//						puts("");
//						printf("found %d %d %d\n", head, tail, i);
					}
					ret += valid;
				}
				printf("%d\n", ret);
			}
		}
	}
	return 0;
}
/*
cd
5
1 b
1 a
2 e
3 cd
3 aa 	

1
0 

d
8
1 a
2 e
1 b
2 n
2 d
3 ba
3 bad
3 badend 

ababa
1
3 aba 

2

*/
