#include<stdio.h>
char type[10][6] = {
	{"    "},{"   |"},{"|   "},{"|  |"},{" -- "},
	{"|\\ |"},{"| \\|"},{"| \\ "},{"  - "},{"|/\\|"}
	};
char Num[10][5] = {
	{4,3,0,3,4},/*0*/
	{0,1,0,1,0},/*1*/
	{4,1,4,2,4},/*2*/
	{4,1,4,1,4},/*3*/
	{0,3,4,1,0},/*4*/
	{4,2,4,1,4},/*5*/
	{4,2,4,3,4},/*6*/
	{4,1,0,1,0},/*7*/
	{4,3,4,3,4},/*8*/
	{4,3,4,1,4}/*9*/
					};
char ALetter[26][5] = {
	{4,3,4,3,0},{},{},{},{4,2,4,2,4},/*ABCDE*/
	{},{},{0,3,4,3,0},{},{},/*FGHIJ*/
	{},{},{},{0,5,0,6,0},{},/*KLMNO*/
	{4,3,4,2,0},{},{4,3,4,7,0},{},{},/*PQRST*/
	{},{},{0,3,0,9,0},{},{0,3,4,1,8},/*UVWXY*/
	{}/*z*/
					};
void PrintALetter(char s[], int n) {
	int a, b, c, tn, t;
	for(a = 0; a < 5; a++) {
		if(a == 0 || a == 2 || a == 4) tn = 1;
		else tn = n;
		for(t = 0; t < tn; t++) {
			for(b = 0; s[b]; b++) {
				if(s[b] == ' ') {putchar(' ');continue;}
				printf("%c", type[ALetter[s[b] - 'A'][a]][0]);
				if(a == 0 || a == 2 || a == 4) {
					for(c = 0; c < n; c++)
						printf("%c", type[ALetter[s[b] - 'A'][a]][1]);
					for(c = 0; c < n; c++)
						printf("%c", type[ALetter[s[b] - 'A'][a]][2]);
				}
				else if(a == 1){
					for(c = 0; c < t; c++)	putchar(' ');
					putchar(type[ALetter[s[b] - 'A'][a]][1]);
					for(; c < n-1; c++) putchar(' ');
					for(c = 0; c < n-t-1; c++)	putchar(' ');
					putchar(type[ALetter[s[b] - 'A'][a]][2]);
					for(; c < n-1; c++) putchar(' ');
				}
				else {
					for(c = 0; c < n-t-1; c++)	putchar(' ');
					putchar(type[ALetter[s[b] - 'A'][a]][1]);
					for(; c < n-1; c++) putchar(' ');
					for(c = 0; c < t; c++)	putchar(' ');
					putchar(type[ALetter[s[b] - 'A'][a]][2]);
					for(; c < n-1; c++) putchar(' ');
				}
				printf("%c", type[ALetter[s[b] - 'A'][a]][3]);
				if(s[b+1] != '\0') putchar(' ');
			}
			puts("");
		}
	}
}			
void PrintNum(char s[], int n) {
	int a, b, c, tn;
	for(a = 0; a < 5; a++) {
		if(a == 0 || a == 2 || a == 4) tn = 1;
		else tn = n;
		while(tn--) {
			for(b = 0; s[b]; b++) {
				if(s[b] == ' ') {putchar(' ');continue;}
				printf("%c", type[Num[s[b] - '0'][a]][0]);
				for(c = 0; c < n; c++)
					printf("%c%c", type[Num[s[b] - '0'][a]][1], type[Num[s[b] - '0'][a]][2]);
				printf("%c", type[Num[s[b] - '0'][a]][3]);
				if(s[b+1] != '\0') putchar(' ');
			}
			puts("");
		}
	}
}
main() {
	int n, m, s, tm, ts, a, b;
	char S[20];

	while(scanf("%d %d %d", &n, &m, &s) == 3) {
		if(n == 0 && m == 0 && s == 0) break;
		s = m*60 + s;
		for(a = s; a >= 0; a--) {
			tm = a/60, ts = a%60;
			if(tm < 10) {S[0] = '0', S[1] = tm + '0';}
			else {S[0] = tm/10 + '0', S[1] = tm%10 + '0';}
			for(b = 0; b < n; b++)	S[2+b] = ' ';
			if(ts < 10) {S[3+n-1] = '0', S[4+n-1] = ts + '0';}
			else {S[3+n-1] = ts/10 + '0', S[4+n-1] = ts%10 + '0';}
			S[5+n-1] = '\0', PrintNum(S, n);
		}
		PrintALetter("HAPPY", n);
		PrintALetter("NEWYEAR", n);
	}
	return 0;
}
