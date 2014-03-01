#include<stdio.h>
#include<string.h>
int main() {
	char s[201];
	int Sum[201] = {0}, i, j, length;
	while(gets(s)) {
		if(!strcmp(s, "0"))	break;
		length = strlen(s);
		for(i = 0, j = length-1; i < length; i++, j--)
			Sum[i] += s[j] - '0';
	}
	for(i = 0; i < 200; i++)
		if(Sum[i] >= 10) { 
			Sum[i+1] += Sum[i]/10;
			Sum[i] %= 10; 
		} 
	i = 200;
	while(Sum[i] == 0 && i >= 0)	i--;
	if(i == -1)	printf("0");
	for(; i >= 0; i--) {
		printf("%d", Sum[i]);
	}
	puts("");
    return 0;
}
