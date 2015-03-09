#include<stdio.h>
int main() {
	int T, x, y, z, w, n, m;
	char s[10000];
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d %d %d %d", &x, &y, &z, &w, &n, &m);
		gets(s), gets(s);		
		int poison = 0, tmp;
		int i, flag = 0;
		if(m <= 0)	flag = 1;
		for(i = 0; s[i] && flag == 0; i++) {
			if(s[i] >= '0' && s[i] <= '9') {
				tmp = s[i]-'0';
				m += poison;
				if(m <= 0)	flag = 1;
				switch(tmp) {
					case 0:break;
					case 1:m += x;break;
					case 2:m += y;break;
					case 3:m += -z;break;
					case 4:m += -w, poison -= n;break;
				}
				if(m <= 0)	flag = 1;
			}
		}
		if(flag)	puts("bye~Rabbit");
		else		printf("%dg\n", m);
	}
	return 0;
}
