#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

int getSuit(char c) {
	switch(c) {
		case 'C': return 0;
		case 'D': return 1;
		case 'H': return 2;
		case 'S': return 3;
	}
}
int getRank(char c) {
	switch(c) {
		case '0' ... '9': return c - '0';
		case 'A': return 1;
		case 'X': return 10;
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
	} 
}

bool suitCmp(pair<int, int> x, pair<int, int> y) {
	if(x.first != y.first)
		return x.first < y.first;
	return x.second < y.second;
}
bool rankCmp(pair<int, int> x, pair<int, int> y) {
	if(x.second != y.second)
		return x.second < y.second;
	return x.first < y.first;
}
int getType(vector< pair<int, int> > cards) {
	vector< pair<int, int> >::iterator it;
	
	sort(cards.begin(), cards.end(), suitCmp);
	if(cards[0].first == cards[4].first) { // all same suit
		for(int i = 0; i < 13; i++) {
			int ok = 1;
			for(int j = 0; j < 5; j++) {
				int r = (i + j)%13 + 1;
				it = find(cards.begin(), cards.end(), make_pair(cards[0].first, r));
				ok &= it != cards.end();
			}
			if(ok)
				return 9;
		}
	}
	
	sort(cards.begin(), cards.end(), rankCmp);
	if(cards[0].second == cards[3].second ||
		cards[1].second == cards[4].second)
			return 8;
			
	sort(cards.begin(), cards.end(), rankCmp);
	if(cards[0].second == cards[2].second &&
		cards[3].second == cards[4].second)
			return 7;
	if(cards[0].second == cards[1].second &&
		cards[2].second == cards[4].second)
			return 7;
			
	sort(cards.begin(), cards.end(), suitCmp);
	if(cards[0].first == cards[4].first)
		return 6;
		
	sort(cards.begin(), cards.end(), suitCmp);
	for(int i = 0; i < 13; i++) {
		int ok = 1;
		for(int j = 0; j < 5; j++) {
			int r = (i + j)%13 + 1;
			for(int k = 0; k < 4; k++) {
				it = find(cards.begin(), cards.end(), make_pair(k, r));
				if(it != cards.end())
					break;
			}
			ok &= it != cards.end();
		}
		if(ok)
			return 5;
	}
	
	sort(cards.begin(), cards.end(), rankCmp);
	if(cards[0].second == cards[2].second ||
		cards[1].second == cards[3].second ||
		 cards[2].second == cards[4].second)
			return 4;
	
	sort(cards.begin(), cards.end(), rankCmp);
	if(cards[0].second == cards[1].second &&
		cards[2].second == cards[3].second)
			return 3;
	if(cards[0].second == cards[1].second &&
		cards[3].second == cards[4].second)
			return 3;
	if(cards[1].second == cards[2].second &&
		cards[3].second == cards[4].second)
			return 3;
			
	sort(cards.begin(), cards.end(), rankCmp);
	for(int i = 1; i < 5; i++)
		if(cards[i].second == cards[i-1].second)
			return 2;
	return 1;
}
int main() {
	int testcase;
	char grid[5][5][5];
	scanf("%d", &testcase);
	while(testcase--) {
		for(int i = 0; i < 5; i++)
			for(int j = 0; j < 5; j++)
				scanf("%s", grid[i][j]);
		int cnt[10] = {};
		for(int i = 0; i < 5; i++) {
			vector< pair<int, int> > cc;
			for(int j = 0; j < 5; j++)
				cc.push_back(make_pair(getSuit(grid[i][j][1]), getRank(grid[i][j][0])));
			int f = getType(cc);
			cnt[f]++;
		}
		
		for(int i = 0; i < 5; i++) {
			vector< pair<int, int> > cc;
			for(int j = 0; j < 5; j++)
				cc.push_back(make_pair(getSuit(grid[j][i][1]), getRank(grid[j][i][0])));
			int f = getType(cc);
			cnt[f]++;
		}
		
		for(int i = 1; i <= 9; i++) {
			if(i > 1)	printf(", ");
			printf("%d", cnt[i]);
		}
		puts("");
		if(testcase)
			puts("");
	}
	return 0;
}
/*
2

AS 2S 3S 4S 5S
AC 2H 3H 5C 4C
AH 2D KC KH 5D
AD 3D KD 9D 8D
XH 3C XC XS 8C

AS 2S 3S 4S 6S
AC 2H 3H 5C 4C
AH 2D KC KH 5D
AD 3D KD 9D 8D
XH 3C XC XS 8C
*/
