#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Swap(x, y) {int t; t = x, x = y, y = t;}
char Hand[5][3], Deck[5][3], flag;

int mask[15][4];
void Count() {
	memset(mask, 0, sizeof(mask));
	int i, t1, t2;
	for(i = 0; i < 5; i++) {
		switch(Hand[i][0]) {
			case '2'...'9': t1 = Hand[i][0]-'0';break;
			case 'T':t1 = 10;break;
			case 'J':t1 = 11;break;
			case 'Q':t1 = 12;break;
			case 'K':t1 = 13;break;
			case 'A':t1 =  1;break;
		} 
		switch(Hand[i][1]) {
			case 'C':t2 = 0;break;
			case 'D':t2 = 1;break;
			case 'H':t2 = 2;break;
			case 'S':t2 = 3;break;
		}
		mask[t1][t2] = 1;
		if(t1 == 1)	mask[14][t2] = 1;
		/*printf("%s ", Hand[i]);*/
	}/*
	puts("");
	system("pause");*/
}
void Stright_flush() {
	int i, j, k;
	for(i = 0; i < 4; i++) {
		for(j = 1; j <= 10; j++) {
			for(k = j; k <= j+4; k++)
				if(mask[k][i] == 0)	break;
			if(k == j+5) { 
				puts("straight-flush"), flag = 1;
				return;
			} 
		}
	}
}
void Four_kind() {
	int i, j;
	for(i = 1; i <= 13; i++) {
		for(j = 0; j < 4; j++)
			if(mask[i][j] == 0)	break;
		if(j == 4) {
			puts("four-of-a-kind"),	flag = 1;
			return;
		}
	}
}
void Full_house() {
	int i, j, sum1, sum2, a, b;
	for(i = 1; i <= 13; i++) {
		for(j = 0, sum1 = 0; j < 4; j++)
			sum1 += mask[i][j];
		if(sum1 == 3) {
			for(a = 1; a <= 13; a++) {
				for(b = 0, sum2 = 0; b < 4; b++)
					sum2 += mask[a][b];
				if(sum2 == 2) {
					puts("full-house"), flag = 1;
					return;
				}
			}
		}
	}
}
void Flush() {
	int i, j, sum;
	for(i = 0; i < 4; i++) {
		for(j = 1, sum = 0; j <= 13; j++)
			sum += mask[j][i];
		if(sum == 5) {
			puts("flush"), flag = 1;
			return;
		}
	}
}
void Stright() {
	int i, j, k;
	for(i = 1; i <= 10; i++) {
		for(j = i; j <= i+4; j++)
			if(mask[j][0] || mask[j][1] || mask[j][2] || mask[j][3])
				continue;
			else
				break;
		if(j == i+5) {
			puts("straight"), flag = 1;
			return;
		}
	}
}
void Three_kind() {
	int i, j, sum;
	for(i = 1; i <= 13; i++) {
		for(j = 0, sum = 0; j < 4; j++)
			sum += mask[i][j];
		if(sum == 3) {
			puts("three-of-a-kind"), flag = 1;
			return;
		}
	}
}
void Two_pairs() {
	int i, j, sum1, sum2, a, b;
	for(i = 1; i <= 13; i++) {
		for(j = 0, sum1 = 0; j < 4; j++)
			sum1 += mask[i][j];
		if(sum1 == 2) {
			for(a = 1; a <= 13; a++) {
				if(a != i) {
						for(b = 0, sum2 = 0; b < 4; b++)
							sum2 += mask[a][b];
						if(sum2 == 2) {
							puts("two-pairs"), flag = 1;
							return;
						}
				}
			}
		}
	}
}
void One_pair() {
	int i, j, sum;
	for(i = 1; i <= 13; i++) {
		for(j = 0, sum = 0; j < 4; j++)
			sum += mask[i][j];
		if(sum == 2) {
			puts("one-pair"), flag = 1;
			return;
		}
	}
}
void High_card() {
	puts("highest-card"), flag = 1;
	return;
}
void ( *Function[9])() = {Stright_flush, Four_kind, Full_house, Flush,
					 Stright, Three_kind, Two_pairs, One_pair, High_card};
void Change(int n, int m, int Case) {
	if(flag)
		return;
	if(n == 5) {
		Count();
		( *Function[Case])();
		return;
	}
	Change(n+1, m, Case);
	Swap(Hand[n][0], Deck[m][0]);Swap(Hand[n][1], Deck[m][1]);
	Change(n+1, m+1, Case);
	Swap(Hand[n][0], Deck[m][0]);Swap(Hand[n][1], Deck[m][1]);
}
main() {
	
	int i;
	while(scanf("%s", &Hand[0]) == 1) {
		for(i = 1; i < 5; i++)
			scanf("%s", &Hand[i]);
		for(i = 0; i < 5; i++)
			scanf("%s", &Deck[i]);
		printf("Hand: ");
		for(i = 0; i < 5; i++)
			printf("%s ", Hand[i]);
		printf("Deck: ");
		for(i = 0; i < 5; i++)
			printf("%s ", Deck[i]);
		printf("Best hand: ");
		for(i = 0, flag = 0; i < 9; i++)
			Change(0, 0, i);
	}
	puts("OLE");
	return 0;
}
