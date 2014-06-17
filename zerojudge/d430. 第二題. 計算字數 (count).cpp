#include<stdio.h>
main() {
	int Ans = 0, a, b;
	char s[10001];
	while(scanf("%s", s) == 1) {
		int flag = 0;
		for(a = 0; s[a]; a++) {
			switch(s[a]) {
				case 'a' ... 'z':flag = 1;break;
				case 'A' ... 'Z':flag = 1;break;
				case '0' ... '9':flag = 1;break;
				default: {
					if(s[a] == '\'') continue;
					if(s[a] == '-') continue;
					if(s[a] < 0) continue;
					Ans += flag, flag = 0;
				}
			}
		}
		if(flag == 1)	Ans++;
	}
	printf("%d\n", Ans);
	return 0;
}
