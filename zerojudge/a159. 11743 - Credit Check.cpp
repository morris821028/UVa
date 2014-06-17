#include<stdio.h>
char s[20];
main() {
	int n, a, t1, t2;
	scanf("%d", &n), getchar();
	while(n--) {
		gets(s);
		for(a = 0; s[a]; a++)	s[a] = (s[a]-'0')*2;
		t1 = s[0]%10+s[0]/10 + s[2]%10+s[2]/10 + s[5]%10+s[5]/10 
		+ s[7]%10+s[7]/10 + s[10]%10+s[10]/10 + s[12]%10+s[12]/10
		+ s[15]%10+s[15]/10 + s[17]%10+s[17]/10;
		t2 = (s[1] + s[3] + s[6] + s[8] + s[11] + s[13] + s[16] + s[18]) /2;
		if((t1+t2)%10)	puts("Invalid");
		else	puts("Valid");
	}
	return 0;
}
