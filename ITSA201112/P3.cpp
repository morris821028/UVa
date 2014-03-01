#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main() {
	char s[1000];
	while(gets(s)) {
		int i, flag = 0;
		for(i = 0; s[i]; i++) {
			switch(s[i]) {
				case '1':printf("a");flag = 1;break;
				case '2':printf("b");flag = 1;break;
				case '3':printf("c");flag = 1;break;
				case '4':printf("d");flag = 1;break;
				case '5':printf("e");flag = 1;break;
				case '6':printf("f");flag = 1;break;
				case '7':printf("g");flag = 1;break;
				case '8':printf("h");flag = 1;break;
				case '9':printf("i");flag = 1;break;
			}
		}
		
		if(flag == 0)	printf("No Solution\n");
		else puts("");
	}
    return 0;
}
