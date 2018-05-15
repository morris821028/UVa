#include <bits/stdc++.h>
using namespace std;

int randRange(int l, int r) {
	return rand()%(r-l+1)+l;
}
char randChar(int l, int r) {
	return rand()%(r-l+1)+l;
}
int main() {
	srand(time(NULL));
	int testcase = 1;
//	printf("%d\n", testcase);
    while (testcase--) {
    	int n = 100000;
    	int l = 'a', r = 'b';
    	static char buf[300005];
    	int head = 100000;
    	int tail = head-1;
    	for (int i = 0; i < n; i++) {
//    		buf[++tail] = randChar(l, r);
			buf[++tail] = i%4 == 0 ? 'a' : 'b';
    		putchar(buf[tail]);
    	}
    	puts("");
    	int q = 100000;
    	printf("%d\n", q);
		for (int i = 0; i < q; i++) {
			int cmd = rand()%3+1;
			if (cmd == 1) {
//				buf[--head] = randChar(l, r);
				--head, buf[head] = head%4 == 0 ? 'a' : 'b';
				if (i > q*9/10)
					buf[tail] = randChar(l, r);
				printf("%d %c\n", cmd, buf[head]);
			} else if (cmd == 2)  {
//				buf[++tail] = randChar(l, r);
				--tail, buf[tail] = tail%4 == 0 ? 'a' : 'b';
				if (i > q*9/10)
					buf[tail] = randChar(l, r);
				printf("%d %c\n", cmd, buf[tail]);
			} else {
//				for (int i = head; i <= tail; i++)
//					putchar(buf[i]);
//				puts("");
				int qn = rand()*rand()%min(tail-head+1, 1000)+1;
				int pos = randRange(head, tail);
				printf("%d ", cmd);
				for (int j = 0; j < qn && pos <= tail; j++, pos++) {
					if (rand()%100)
						putchar(buf[pos]);
					else
						putchar(randChar(l, r));
				}
				puts("");
			}
		}
    }
	return 0;
}
