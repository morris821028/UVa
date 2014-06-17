#include<stdio.h>
main() {
	int t, a, b, c, d;
	char s[101];
	scanf("%d", &t), getchar();
	while(t--) {
		gets(s);
		int Queue[101], Qt = 0, Ans = 0;
		Queue[Qt++] = s[0]-'0';
		for(a = 1; s[a]; a++) {
			switch(s[a]) {
				case '+':Queue[Qt++] = s[a+1]-'0', a++;break;
				case '*':Queue[Qt-1] *= (s[a+1]-'0'), a++;break;
			}
		}
		for(a = 0, Ans = 0; a < Qt; a++)	Ans += Queue[a];
		printf("%d\n", Ans);
	}
	return 0;
}
