#include<stdio.h>
main() {
	char s[1000];
	while(scanf("%s", s) == 1)  {
		int a, b;
		int ra = 0, rv = 0, la = 0, lv = 0; 
		int flag = 1, t = 0, var; 
		for(a = 0; s[a]; a++) {
			if(s[a] == '=') {a++;break;} 
			else if(s[a] == '-') {
				rv += t * flag, t = 0;
				flag = -1;
			} 
			else if(s[a] == '+') {
				rv += t * flag, t = 0;
				flag = 1;
			} 
			else if(s[a] >= '0' && s[a] <= '9') 
				t = t*10 + s[a] - '0'; 
			else { /*s[a] == '?'*/ 
				ra += ((t == 0) ? 1 : t) * flag;
				t = 0, flag = 1, var = s[a]; 
			} 
		} 
		rv += t*flag; 
		flag = 1, t = 0;
		for(; s[a]; a++) {
			if(s[a] == '-') {
				lv += t * flag, t = 0;
				flag = -1;
			} 
			else if(s[a] == '+') {
				lv += t * flag, t = 0;
				flag = 1;
			} 
			else if(s[a] >= '0' && s[a] <= '9') 
				t = t*10 + s[a] - '0'; 
			else { /*s[a] == 'a'*/ 
				la += ((t == 0) ? 1 : t) * flag;
				t = 0, flag = 1, var = s[a]; 
			} 
		} 
		lv += t*flag;
		if(lv - rv == 0) 
			printf("%c=0.000\n", var); 
		else 
			printf("%c=%.3lf\n", var, (lv-rv)/(double)(ra-la)); 
	} 
	return 0; 
}
