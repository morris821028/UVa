#include<stdio.h>
int main() {
	char s[1001];
	while(gets(s)) {
		int i, flag = 0, count = 0;
		for(i = 0; s[i]; i++) {
			if((s[i] >= 'A' && s[i] <= 'Z') || 
				(s[i] >= 'a' && s[i] <= 'z'))
					flag = 1;
			else {
				count += flag;
				flag = 0;
			}
		}
		count += flag;
		printf("%d\n", count);
	}
    return 0;
}
