#include <stdio.h>
#define empty 0
int ans;
int solve(int sum, int target, char *c) {
	int flag = 0, leaf = 0, token, neg;
	while(*c == ' ' || *c == '\n')
		*c = getchar();
	if(*c == '(') {
		token = 0, flag = 0, neg = 1;
		while(*c = getchar()) {
			if(*c >= '0' && *c <= '9')
				token = token*10 + *c-'0', flag = 1;
			else {
				if(*c == '-')	neg = -1;
				else break;
			} 
		}
		token *= neg;
		while(*c == ' ' || *c == '\n')
			*c = getchar();
		if(flag == 0) {
			return empty;
		}
		int left = solve(sum+token, target, c);
		while((*c = getchar()) != '(');
		int right = solve(sum+token, target, c);
		while((*c = getchar()) != ')');
		if(left == 0 && right == 0) {
			if(sum+token == target)
				ans = 1;
		}
		return 1;
	}
}
int main() {
	int target;
	char c;
	while(scanf("%d", &target) == 1) {
		ans = 0;
		c = getchar();
		solve(0, target, &c);
		if(ans == 1)
			puts("yes");
		else
			puts("no");
	}
    return 0;
}
