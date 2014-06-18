#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>	
char s[10000000];
int main() {
	int error = 0, i, j, k;
	while(gets(s)) {
		if(s[0] == '\0')
			puts(""), error = 0;
		if(error == 1)	continue;
		int cont = 0;
		for(i = 0; s[i] && error == 0 && cont == 0; i++) {
			switch(s[i]) {
				case ':':
					if(s[i+1]) {
						if(s[i+1] != '=')
							error = 1;
						else
							puts(":="), i++;
					} else
						error = 1;
					break;
				case '+':puts("+");break;
				case '-':
					if(s[i+1] == '-') {
						cont = 1;
						break;
					} else
						puts("-");break;
				case ')':puts(")");break;
				case '(':puts("(");break;
				case ',':puts(",");break;
				case ';':puts(";");break;
				case ' ':break;
				default:
					int flag = 0;
					for(j = i; s[j]; j++) {						
						if(s[j] == ':')	break;
						if(s[j] == '+')	break;
						if(s[j] == '-')	break;
						if(s[j] == '(')	break;
						if(s[j] == ')')	break;
						if(s[j] == ',')	break;
						if(s[j] == ';')	break;
						if(s[j] == ' ')	break;
						if(
						(!(s[j] >= 'a' && s[j] <= 'z')) && 
						(!(s[j] >= 'A' && s[j] <= 'Z')) &&
						(!(s[j] >= '0' && s[j] <= '9')) &&
						s[j] != '_'
						) {
							/*printf("exist %c\n", s[j]), */flag = 1;break;
						}

					}
/*				printf("flag :%d\n", flag);*/
				if(flag == 1)
					error = 1;
				if(j-i > 32)	error = 1;
				else {
						for(k = i; k < j; k++)
							if(!(s[k] >= '0' && s[k] <= '9'))
								break;
						if(k == j && j-i > 8)	error = 1;
						if(error == 0) {
							for(k = i; k < j; k++)
								printf("%c", s[k]);
							puts("");
						}
						i = j-1;
				}
			}
		}
		if(error)	puts("TOKEN_ERROR");
	}
    return 0;
}/*
A1:= A+(-B)

A123_A123 )
01.2 A B
C

:= A beGIn

aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
*/
