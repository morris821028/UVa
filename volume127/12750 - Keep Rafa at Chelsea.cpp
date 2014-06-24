#include <stdio.h> 

int main() {
	int testcase, cases = 0;
	int N;
	char token[10];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &N);
		int win = 0, cnt = 0, Y = 0;
		while(N--) {
			scanf("%s", token);
			if(win)	continue;
			if(token[0] == 'W')
				cnt = 0;
			else
				cnt++, win |= cnt >= 3;
			Y++; 
		}
		printf("Case %d: ", ++cases);
		if(win)
			printf("%d\n", Y);
		else
			puts("Yay! Mighty Rafa persists!");
	}
	return 0;
}
/*
3
5
L
D
L
D
W
6
L
D
W
L
L
L
3
D
D
W
*/
