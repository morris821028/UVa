#include<stdio.h>
int Input() {  
    char cha;  
    unsigned int x = 0;  
    while(cha = getchar())  
        if(cha != ' ' && cha != '\n' || cha == EOF) break;  
    if(cha == EOF) return EOF; 
    x = cha-48;  
    while(cha = getchar()) {  
        if(cha == ' ' || cha == '\n') break;  
        x = x*10 + cha-48;  
    }  
    return x;  
}
main() {
	int n, m, A[1001], a, b, temp, stp;
	char str[10001];
	while(scanf("%d %d", &n, &m) == 2) {
		for(a = 0, stp = 0; a < n; a++)
			A[a] = Input();
		for(b = 0; a < m; a++, b++) {
			A[a] = Input();
			temp = A[b] - A[a];
			if(temp < 0) temp = -temp;
			temp = temp / n + (temp%n != 0);
			if(temp < 100 && temp > 9)
				str[stp++] = temp/10 + '0', str[stp++] = temp%10 + '0';
			else if(temp < 10)
				str[stp++] = temp +'0';
			else
				str[stp++] = '1', str[stp++] = '0', str[stp++] = '0';
			str[stp++] = ' ';
		}
		str[stp] = '\0';
		puts(str);
	}
	return 0;
}
