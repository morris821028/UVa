#include<stdio.h>
int main() {
	char s[201];
	while(gets(s)) {
		if(s[0] == '*')	break;
		int st = 0, i, find = 0, Sum = 0;
		for(i = 1; s[i]; i++) {
			if(s[i] == '/') {
				if(Sum == 1000000)	find++;
				Sum = 0;
			}
			switch(s[i]) {
				case 'W':Sum += 1000000;break;
				case 'H':Sum +=  500000;break;
				case 'Q':Sum +=  250000;break;
				case 'E':Sum +=  125000;break;
				case 'S':Sum +=   62500;break;
				case 'T':Sum +=   31250;break;
				case 'X':Sum +=   15625;break;
			}
		}
		printf("%d\n", find);
	}
    return 0;
}
