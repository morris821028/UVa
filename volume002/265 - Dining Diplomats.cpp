#include <stdio.h> 
#include <string.h>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <algorithm>
using namespace std;

struct State {
	string name, lang;
	set<string> g;
	int lang_mask[128];
	int read() {
		string line;
		if (getline(cin, line)) {
			assert(line.length() > 0);
			g.clear();
			stringstream sin(line);
			sin >> name >> lang;
			while (sin >> line)
				g.insert(line);
			
			g.insert(name); // what the fuck, same country in test data.
			memset(lang_mask, 0, sizeof(lang_mask));
			for (int i = 0; i < lang.length(); i++)
				lang_mask[lang[i]] = 1;
			return 1;
		} else {
			return 0;
		}
	}
	int hasCommon(const State &a) {
		for (int i = 0; i < 128; i++)
			if (lang_mask[i] && a.lang_mask[i])
				return 1;
		return 0;
	}
	char common(const State &a) {
		for (int i = 0; i < 128; i++)
			if (lang_mask[i] && a.lang_mask[i])
				return i;
		return '-';
	}
} C[10];
int g[10][10];
int dp[1<<10][10], from[1<<10][10];

int tsp(int u, int last) {
	if (dp[u][last] != -1)	return dp[u][last];
	int &ret = dp[u][last];
	ret = 0;
	for (int i = 0; i < 10; i++) {
		if (((u>>i)&1) && g[last][i]) {
			int f = tsp(u^(1<<i), i);
			if (f) {
				from[u][last] = i;
				return ret = 1;				
			}
		}
	}
	return ret;
}
int main() {
	while (true) {
		for (int i = 0; i < 10; i++) {
			if (!C[i].read())
				return 0;
		}
		
		memset(g, 0, sizeof(g));
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (C[i].g.count(C[j].name) && C[j].g.count(C[i].name) 
					&& C[i].hasCommon(C[j])) {
					g[i][j] = 1;
				}
			}
		}
		
//		for (int i = 0; i < 10; i++, puts(""))
//			for (int j = 0; j < 10; j++)
//				printf("%d ", g[i][j] > 0);
		
		memset(dp, -1, sizeof(dp));
		dp[0][0] = 1;
		int flag = tsp((1<<10)-1, 0);
		if (flag) {
			int p = (1<<10)-1, q = 0;
			int seat[10];
			for (int i = 0; i < 10; i++) {
				seat[i] = q;
				q = from[p][q];
				p = p^(1<<q);
			}
			for (int i = 0; i < 10; i++) 
				printf("%d %c %s %c\n", i+1, C[seat[i]].common(C[seat[(i-1+10)%10]]), 
					C[seat[i]].name.c_str(), C[seat[i]].common(C[seat[(i+1+10)%10]]));
		} else {
			puts("NO SOLUTION EXISTS");
		}
		puts("");
		
		while (getchar() != '\n');
	}
	return 0;
}
/*
USA EF CHN GBR USR FRA FRG JPN ISR POR KOR
CHN CFE USA GBR FRA FRG
GBR ER USA CHN USR FRA FRG JPN ISR POR KOR
USR RF USA GBR FRA FRG
FRA F USA CHN GBR USR FRG JPN ISR POR
FRG ERG USA CHN GBR USR FRA JPN ISR POR
JPN JHG USA GBR FRA FRG JPN ISR POR KOR
ISR HER USA GBR FRA FRG JPN KOR
POR PGE USA GBR FRA FRG JPN
KOR KEC USA GBR USR JPN ISR

USA EF CHN GBR USR FRA FRG JPN ISR POR KOR
CHN CFE USA GBR FRA FRG
GBR ER USA CHN USR FRA FRG JPN ISR POR KOR
USR RF
FRA F USA CHN GBR USR FRG JPN ISR POR
FRG ERG USA CHN GBR USR FRA JPN ISR POR
JPN JHG USA GBR FRA FRG JPN ISR POR KOR
ISR HER USA GBR FRA FRG JPN KOR
POR PGE USA GBR FRA FRG JPN
KOR KEC USA GBR USR JPN ISR

TLC ADBE TQA DAO FHH NUW FAB PSR FEQ QPA KCW
TQA EB TLC DAO PSR FEQ KCW
DAO B TLC TQA FHH FAB PSR FEQ QPA KCW
FHH B TLC DAO PSR KCW
NUW DBE TLC
FAB D TLC DAO PSR FEQ QPA
PSR AC TLC TQA DAO FHH FAB QPA
FEQ CB TLC TQA DAO FAB QPA
QPA D TLC DAO FAB PSR FEQ KCW
KCW AE TLC TQA DAO FHH QPA



*/
