#include <stdio.h> 
#include <string.h>
#include <deque>
#include <queue>
#include <set>
using namespace std;
struct state {
	int v[64];
	state() {
		memset(v, 0, sizeof(v));
	}
	bool operator<(const state &x) const {
		return memcmp(v, x.v, sizeof(state)) < 0;
	}
};
deque<int> pile[7];
queue<int> hand;
set<state> record;
void reduce(deque<int> &pile) {
	while(pile.size() >= 3) {
		int n = pile.size();
		if((pile[0] + pile[1] + pile[n-1])%10 == 0) {
			hand.push(pile[0]), hand.push(pile[1]), hand.push(pile[n-1]);
			pile.pop_front();
			pile.pop_front();
			pile.pop_back();
		} else if((pile[0] + pile[n-2] + pile[n-1])%10 == 0) {
			hand.push(pile[0]), hand.push(pile[n-2]), hand.push(pile[n-1]);
			pile.pop_front();
			pile.pop_back();
			pile.pop_back();
		} else if((pile[n-3] + pile[n-2] + pile[n-1])%10 == 0) {
			hand.push(pile[n-3]), hand.push(pile[n-2]), hand.push(pile[n-1]);
			pile.pop_back();
			pile.pop_back();
			pile.pop_back();
		} else {
			break;
		}
	}
}
int main() {
	int x;
	while(true) {
		while(!hand.empty())
			hand.pop();
		for(int i = 0; i < 7; i++) 
			pile[i].clear();
			
		for(int i = 0; i < 52; i++) {
			scanf("%d", &x);
			if(x == 0)	return 0;
			hand.push(x);
		}
		for(int i = 0; i < 7; i++)
			pile[i].push_back(hand.front()), hand.pop();
		
		for(int i = 0; i < 7; i++)
			pile[i].push_back(hand.front()), hand.pop();
		
		int end = 0, loop = 14;
		while(!end) {
			for(int i = 0; i < 7; i++) {
				if(pile[i].size() == 0)
					continue;
				loop++;
				pile[i].push_back(hand.front()), hand.pop();
				reduce(pile[i]);
				if(hand.size() == 52) {
					printf("Win : %d\n", loop);
					end = 1;
					break;
				}
				if(hand.size() == 0) {
					printf("Loss: %d\n", loop);
					end = 1;
					break;
				}
				state s;
				int m = 0;
				for(int j = 0; j < 7; j++) {
					for(int k = 0; k < pile[j].size(); k++)
						s.v[m++] = pile[j][k];
					s.v[m++] = 15;
				}
				queue<int> q = hand;
				while(!q.empty())
					s.v[m++] = q.front(), q.pop();
				s.v[m++] = 15;
				if(record.find(s) != record.end()) {
					printf("Draw: %d\n", loop);
					end = 1;
					break;
				}
				record.insert(s);
			}
		}
	}
	return 0;
}
