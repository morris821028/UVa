#include<stdio.h>
#include<stdlib.h>
int ch1[10][3] = {/*add1*/
		{8,-1},{7,-1},{-1},{9,-1},{-1},
		{6,9,-1},{8,-1},{-1},{-1},{8,-1}
	};
int ch2[10][4] = {/*minus*/
		{-1},{-1},{-1},{-1},{-1},
		{-1},{5,-1},{1,-1},{0,6,9,-1},{3,5,-1}
	};
int ch3[10][3] = {/*no*/
		{6,9,-1},{-1},{3,-1},{2,5,-1},{-1},
		{3,-1},{0,9,-1},{-1},{-1},{0,6,-1}
	};
int flag, left, right;
char s[1001];
void Calu1() {
	int a, neg = 1, tmp = 0;
	left = right = 0;
	for(a = 0; s[a] && s[a] != '='; a++) {
		if(s[a] >= '0' && s[a] <= '9')
			tmp = tmp*10 + s[a] - '0';
		else {
			left += tmp * neg;
			if(s[a] == '+')	neg = 1;
			else neg = -1;
			tmp = 0;
		}
	}
	left += tmp * neg, tmp = 0, neg = 1;
	for(a ++; s[a] && s[a] != '#'; a++) {
		if(s[a] >= '0' && s[a] <= '9')
			tmp = tmp*10 + s[a] - '0';
		else {
			right += tmp * neg;
			if(s[a] == '+')	neg = 1;
			else neg = -1;
			tmp = 0;
		}
	}
	right += tmp * neg;
}
void Calu2(int x, int s1, int y, int s2, int t1, int t2) {
	int a, v = 1, tl = left, tr = right;
	int neg = 1;
	if(x == y) return;
	for(a = x+1; s[a]; a++)
		if(s[a] >= '0' && s[a] <= '9')	v *= 10;
		else	break;
	for(a = x-1; a >= 0; a--)
		if(s[a] == '-') neg = -1;
		else if(s[a] == '+')neg = 1;
		else break;
	if(s1 == 0)	tl -= (t1-(s[x]-'0'))*v*neg;
	else	tr -= (t1-(s[x]-'0'))*v*neg;
	if(y != -1) {
		for(a = y+1, v = 1, neg = 1; s[a]; a++)
			if(s[a] >= '0' && s[a] <= '9')	v *= 10;
			else	break;
		for(a = y-1; a >= 0; a--)
			if(s[a] == '-') neg = -1;
			else if(s[a] == '+')neg = 1;
		else break;
		if(s2 == 0)	tl -= (t2-(s[y]-'0'))*v*neg;
		else tr-= (t2-(s[y]-'0'))*v*neg;
	}
	if(tl == tr) {
		flag = 1;
		for(a = 0; s[a] && s[a] != '#'; a++)
			printf("%c", s[a]);
		puts("#");
	}
}
main() {
	int a, b, c, d;
	while(scanf("%s", s) == 1) {
		flag = 0;
		for(a = 0; s[a]; a++)
			if(s[a] == '#') flag = 1;
		if(flag == 0) continue;
		else flag = 0;
		Calu1();
		int set1 = 0, set2 = 0;
		for(a = 0; s[a] && flag == 0 && s[a] != '#'; a++)
			if(s[a] >= '0' && s[a] <= '9') {
				int t1 = s[a]-'0';
				for(b = 0; ch3[t1][b] != -1; b++) {
					s[a] = ch3[t1][b]+'0';
					Calu2(a, set1, -1, set2, t1, -1);
					if(flag)	break;
				}
				for(b = 0; ch1[t1][b] != -1 && flag == 0; b++) {
					s[a] = ch1[t1][b]+'0', set2 = 0;
					for(c = 0; s[c] && s[c] != '#' && flag == 0; c++) {
						if(s[c] >= '0' && s[c] <= '9') {
							int t2 = s[c]-'0';
							for(d = 0; ch2[t2][d] != -1 && flag == 0; d++) {
								s[c] = ch2[t2][d]+'0';
								Calu2(a, set1, c, set2, t1, t2);
								if(flag)	break;
							}
							s[c] = t2+'0';
						} else {
							if(s[c] == '=') set2 = 1;
						}
					}
				}
				for(b = 0; ch2[t1][b] != -1 && flag == 0; b++) {
					s[a] = ch2[t1][b]+'0', set2 = 0;
					for(c = 0; s[c] && s[c] != '#' && flag == 0; c++) {
						if(s[c] >= '0' && s[c] <= '9') {
							int t2 = s[c]-'0';
							for(d = 0; ch1[t1][d] != -1 && flag == 0; d++) {
								s[c] = ch1[t1][d]+'0';
								Calu2(a, set1, c, set2, t1, t2);
								if(flag)	break;
							}
							s[c] = t2+'0';
						} else {
							if(s[c] == '=')	set2 = 1;
						}
					}
				}
				s[a] = t1+'0';
			} else {
				if(s[a] == '=')	set1 = 1;
			}
			
		if(!flag)	puts("No");
	}
	return 0;
}
