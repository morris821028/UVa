#include<stdio.h>
#include<string.h>
char s1[1001], s2[1001], cc[2];
char Maxv[11] = "2147483647";
int compare(char s1[], int l1, char s2[], int l2) {
	if(l1 < l2)	return 0;
	if(l1 > l2)	return 1;
	int a;
	for(a = 0; a < l1; a++)
		if(s1[a] > s2[a])
			return 1;
		else if(s1[a] < s2[a])
			return 0;
	return 0;
}
void Mult(char s1[], int l1, char s2[], int l2) {
	int M[2001] = {};
	int a, b, c, d;
	for(a = 0, c = l1-1; a < l1; a++, c--)
		for(b = 0, d = l2-1; b < l2; b++, d--)
			M[a+b] += (s1[c]-'0')*(s2[d]-'0'), M[a+b+1] += M[a+b]/10, M[a+b] %= 10;
	char s3[2001];
	a = l1+l2+1;
	while(M[a] == 0) a--;
	for(b = 0; a >= 0;b++, a--)
		s3[b] = M[a] + '0';
	if(compare(s3, b, Maxv, 10) == 1)
		puts("result too big");
}
void Add(char s1[], int l1, char s2[], int l2) {
	int M[2001] = {};
	int a, b;
	for(a = 0, b = l1-1; a < l1; a++, b--)
		M[a] = s1[b] - '0';
	for(a = 0, b = l2-1; a < l2; a++, b--)
		M[a] += s2[b] - '0', M[a+1] += M[a]/10, M[a] %= 10;
	for(a = 0; a < l1+l2; a++)
		M[a+1] += M[a]/10, M[a] %= 10;
	char s3[2001];
	a = l1+l2;
	while(M[a] == 0) a--;
	for(b = 0; a >= 0;b++, a--)
		s3[b] = M[a] + '0';
	if(compare(s3, b, Maxv, 10) == 1)
		puts("result too big");
}
main() {
	int a, l1, l2;
	while(scanf("%s %s %s", s1, cc, s2) == 3) {
		printf("%s %s %s\n", s1, cc, s2);		
		l1 = strlen(s1), l2 = strlen(s2);
		
		if(compare(s1, l1, Maxv, 10) == 1)
			puts("first number too big");
		if(compare(s2, l2, Maxv, 10) == 1)
			puts("second number too big");
		if(cc[0] == '+')
			Add(s1, l1, s2, l2);
		else
			Mult(s1, l1, s2, l2);
	}
	return 0;
}
