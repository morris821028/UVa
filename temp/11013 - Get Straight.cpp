#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

int card2Idx(char s[]) {
	int x, suit;
	switch (s[0]) {
		case '0'...'9': x = s[0] - '0';break;
		case 'A': x = 1;break;
		case 'T': x = 10;break;
		case 'J': x = 11;break;
		case 'Q': x = 12;break;
		case 'K': x = 13;break; 
	}
	switch (s[1]) {
		case 'S':suit = 0;break;
		case 'H':suit = 1;break;
		case 'D':suit = 2;break;
		case 'C':suit = 3;break;
	}
	return suit * 13 + x - 1;
}
int getPrize(int hand[]) {
	int m[13] = {};
	for (int i = 0; i < 5; i++)
		m[hand[i]%13]++;
	// run of 5
	for (int i = 0; i < 13; i++) {
		int ok = 1;
		for (int j = 0; j < 5 && ok; j++) 
			ok &= m[(i+j)%13] > 0;
		if (ok)	return 100;
	}
	// run of 4
	for (int i = 0; i < 13; i++) {
		int ok = 1;
		for (int j = 0; j < 4 && ok; j++) 
			ok &= m[(i+j)%13] > 0;
		if (ok)	return 10;
	}
	// run of 3 + run of 2 // 3 4 5, 3 4
	for (int i = 0; i < 13; i++) {
		int ok = 1, r[13] = {}, h = 0;
		for (int j = 0; j < 13; j++)
			r[j] = m[j];
		for (int j = 0; j < 3; j++) 
			ok &= --r[(i+j)%13] >= 0;
		for (int j = 0; j < 13 && ok; j++) {
			if (r[j] > 0) {
				if (r[(j+1)%13] > 0 || r[(j+12)%13] > 0)
					h = 1;
			}
		}
		ok &= h;
		if (ok)	return 5;
	}
	// run of 3
	for (int i = 0; i < 13; i++) {
		int ok = 1;
		for (int j = 0; j < 3 && ok; j++) 
			ok &= m[(i+j)%13] > 0;
		if (ok)	return 3;
	}
	// run of 2 + run of 2 // 3 4, 3 4
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 13; j++) {
			if (!m[i] || !m[j])
				continue;
			int r[13] = {};
			for (int k = 0; k < 13; k++)
				r[k] = m[k];
			int ok = 1;
			r[i]--, r[j]--;
			if (r[i] < 0 || r[j] < 0)
				continue;
			if (!r[(i+1)%13])
				continue;
			r[(i+1)%13]--;
			if (!r[(j+1)%13])
				continue;
			r[(j+1)%13]--;
			return 1;
		} 
	}
	return 0;
}
double testExchange(int hand[]) {
	int used[13] = {};
	double e = 0;
	for (int i = 0; i < 5; i++)
		used[hand[i]%13]++;
	for (int i = 0; i < 13; i++) {
		int A[5];
		A[4] = i;
		for (int j = 0; j < 4; j++)
			A[j] = hand[j];
		int p = (4 - used[i]) * getPrize(A);
		e += p;
	} 
//	printf("%d %d %d %d %d\n", P[100], P[10], P[5], P[3], P[1]);
	return e - 1 * 47.0;
}
void printCard(int x) {
	switch (x%13) {
		case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:
			printf("%d", x%13 + 1);break;
		case 0: printf("A");break;
		case 9: printf("T");break;
		case 10: printf("J");break;
		case 11: printf("Q");break;
		case 12: printf("K");break; 
	}
	switch (x/13) {
		case 0:printf("S");break;
		case 1:printf("H");break;
		case 2:printf("D");break;
		case 3:printf("C");break;
	}
}
int main() {	
//freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	char s[16];
	while (true) {
		int hand[5];
//		set<string> S; 
		for (int i = 0; i < 5; i++) {
			if (scanf("%s", s) == 1 && s[0] != '#') {
				
			} else
				return 0;
//			assert(S.count(s) == 0);
//			S.insert(s);
			hand[i] = card2Idx(s);
		}
		
		double o = getPrize(hand) * 47.0;
		double maxe = -1e+30;
		int ret = 0;
		for (int i = 0; i < 5; i++) {
			swap(hand[i], hand[4]);
			double e = testExchange(hand);
			if (e > maxe)
				maxe = e, ret = hand[4];
//			printCard(hand[4]);
//			printf(" %lf\n", e);
			swap(hand[i], hand[4]);
		}
//		printf("%.0lf %.0lf\n", o, maxe);
		if (o < maxe) {
			printf("Exchange ");
			printCard(ret);
			puts("");
		} else {
			puts("Stay");
		}
	}
	return 0;
}
/*
3H 4C 4H 5H TH
4H 4H 5H 3H 3H
4H 4C 5H 3H 3C
3H 4C TH 3C 4H 

6C 8D TD 6H TH 
6H 5H KS 4D 6D 
KS QH AS 7D TD 
2C AC 9H 6D JH 
7H 2H 3H 5S 3D 
4H 3H QS JC 7S 
4C 7D 2C 5H KC 
KH 3C 4H 3S QH 
QC 9C TH 9S 5S 
AH TH 3D 8C QS 


TH JH QH KH AH
2H TC 5D 3S 6C
2S 5S 8D JC JH
AH 5H 9C 2D 5C
AH KH 3H 4H 5C 
TH QH AH 3H 5H

#
*/
