#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int suitW(char c) {
	switch(c) {
		case 'C':return 0;
		case 'D':return 1;
		case 'H':return 2;
		case 'S':return 3;
	}
}
int cardW(char c) {
	switch(c) {
		case '2'...'9':return c - '0';
		case 'T':return 10;
		case 'J':return 11;
		case 'Q':return 12;
		case 'K':return 13;
		case 'A':return 14;
	}
}
char decideTrump(const char c1[], const char c2[]) {
	if(cardW(c1[0]) != cardW(c2[0]))
		return cardW(c1[0]) > cardW(c2[0]) ? c1[1] : c2[1];
	return suitW(c1[1]) > suitW(c2[1]) ? c1[1] : c2[1];
}
int leaderCmp(string c1, string c2) {
	if(cardW(c1[0]) != cardW(c2[0]))
		return cardW(c1[0]) > cardW(c2[0]);
	return suitW(c1[1]) > suitW(c2[1]);
}
string leaderPlay(vector<string> &hand, char trump) {
	sort(hand.begin(), hand.end(), leaderCmp);
	int h = hand[0][0];
	for(vector<string>::iterator it = hand.begin(); 
		it != hand.end(); it++) {
		if((*it)[1] == trump && (*it)[0] == h) {
			string ret = *it;
			hand.erase(it);
			return ret;
		}
	}
	string ret = hand[0];
	hand.erase(hand.begin());
	return ret;
}
string followerPlay(vector<string> &hand, char suit, char trump) {
	sort(hand.begin(), hand.end(), leaderCmp);
	for(vector<string>::iterator it = hand.begin(); 
		it != hand.end(); it++) {
		if((*it)[1] == suit) {
			string ret = *it;
			hand.erase(it);
			return ret;
		}
	}
	for(vector<string>::iterator it = hand.begin(); 
		it != hand.end(); it++) {
		if((*it)[1] == trump) {
			string ret = *it;
			hand.erase(it);
			return ret;
		}
	}
	string ret = hand[0];
	hand.erase(hand.begin());
	return ret;
}
int main() {
	char deckCard[52][128];
	const int tricks = 10;
	do {
		for(int i = 0; i < 52; i++) {
			scanf("%s", deckCard[i]);
			if(!strcmp(deckCard[i], "#"))
				return 0;
		}
		vector<string> hand[5];
		for(int i = 0, j = 0; i < 50; i++, j = (j+1)%5) {
			hand[j].push_back(deckCard[i]);
		}
		
		char trump = decideTrump(deckCard[50], deckCard[51]);
		int leader = 0;
		int scores[5] = {};
		
		for(int i = 0; i < tricks; i++) {
			vector< pair<string, int> > desk;
			desk.push_back(make_pair(leaderPlay(hand[leader], trump), leader));
			char suit = desk[0].first[1];
			for(int j = (leader + 1)%5, k = 0; k < 4; j = (j+1)%5, k++) {
				desk.push_back(make_pair(followerPlay(hand[j], suit, trump), j));
			}
			int maxCardW = -1;
			for(int j = 0; j < desk.size(); j++) {
				// printf("PLAYER %d play %s\n", desk[j].second + 1, desk[j].first.c_str());
				if(desk[j].first[1] == trump && suit != trump) {
					suit = trump;
					maxCardW = cardW(desk[j].first[0]);
					leader = desk[j].second;
				}
				if(suit == desk[j].first[1] && cardW(desk[j].first[0]) > maxCardW) {
					maxCardW = cardW(desk[j].first[0]);
					leader = desk[j].second;
				}
			}
			/*
			printf("PLAYER %d is the winner\n", leader + 1);
			for(int j = 0; j < 5; j++) {
				for(int k = 0; k < hand[j].size(); k++)
					printf(" %2d%c ", cardW(hand[j][k][0]), hand[j][k][1]);
				puts("");
			}*/
			for(int j = 0; j < desk.size(); j++) {
				if(desk[j].first[1] == 'H') {
					// printf("GET %d\n", cardW(desk[j].first[0]));
					scores[leader] += cardW(desk[j].first[0]);
				}
			}
		}
		printf("%3d", scores[4]);
		for(int i = 0; i < 4; i++)
			printf("%3d", scores[i]);
		puts("");
	} while(true);
	return 0;
}
/*
TS QC 8S 8D QH 2D 3H KH 9H 2H TH KS KC
9D JH 7H JD 2S QS TD 2C 4H 5H AD 4D 5D
6D 4S 9S 5S 7S JS 8H 3D 8C 3S 4C 6S 9C
AS 7C AH 6H KD JC 7D AC 5C TC QD 6C 3C
#
*/
