// bfs, TLE
#include <stdio.h> 
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<string, string> a, pair<string, string> b) {
	return a.first.length() > b.first.length();
}
int matchSuffix(string S, string T) {
	if (S.length() > T.length())
		return 0;
	for (int i = S.length() - 1, j = T.length() - 1; i >= 0; i--, j--)
		if (S[i] != T[j])
			return 0;
	return 1;
}
string replaceSuffix(string T, string S) {
//	cout << T << ", " << S << endl; 
	T = T.substr(0, T.length() - S.length());
//	cout << T + S << endl;
	return T + S;
}
int main() {
	string A, B, x, y;
	int M, N, cases = 0;
	while (cin >> A >> B >> M) {
		vector< pair<string, string> > D;
		for (int i = 0; i < M; i++) {
			cin >> x >> y;
			D.push_back(make_pair(x, y));
		}
		sort(D.begin(), D.end(), cmp);
		N = (int) A.length();
		map<string, int> R;
		R[A] = 1;
		
		for (int i = 0; i < N; i++) {
			map<string, int> nextR;
			int update = 0;
			
			nextR = R;
			do {
				update = 0;
				for (map<string, int>::iterator it = nextR.begin(); 
					it != nextR.end(); it++) {
					for (int j = 0; j < M; j++) {
						if (matchSuffix(D[j].first, it->first)) {
							int &ret = nextR[replaceSuffix(it->first, D[j].second)];
							if (ret == 0)	ret = 0x3f3f3f3f, update = 1;
							ret = min(ret, it->second + 1);
						}
					}
				}
			} while (update == 1);
			
			// sieve
			R.clear();
			for (map<string, int>::iterator it = nextR.begin(); 
				it != nextR.end(); it++) {
				if (it->first[0] == B[i]) {
					string key = it->first.substr(1);
					R[key] = it->second;
//					printf("%s %d\n", key.c_str(), it->second);
				}
			}
		}
		
		printf("Case %d: ", ++cases);
		if (R.size() == 0)
			printf("No solution\n");
		else
			printf("%d\n", R[""] - 1);
	}
	return 0;
}
/*
AAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBB 20
ABBBBBBBBBBBBBBBBBBB BAAAAAAAAAAAAAAAAAAA
ABBBBBBBBBBBBBBBBBB  BAAAAAAAAAAAAAAAAAA 
ABBBBBBBBBBBBBBBBB   BAAAAAAAAAAAAAAAAA  
ABBBBBBBBBBBBBBBB    BAAAAAAAAAAAAAAAA   
ABBBBBBBBBBBBBBB     BAAAAAAAAAAAAAAA    
ABBBBBBBBBBBBBB      BAAAAAAAAAAAAAA     
ABBBBBBBBBBBBB       BAAAAAAAAAAAAA      
ABBBBBBBBBBBB        BAAAAAAAAAAAA       
ABBBBBBBBBBB         BAAAAAAAAAAA        
ABBBBBBBBBB          BAAAAAAAAAA         
ABBBBBBBBB           BAAAAAAAAA          
ABBBBBBBB            BAAAAAAAA           
ABBBBBBB             BAAAAAAA            
ABBBBBB              BAAAAAA             
ABBBBB               BAAAAA              
ABBBB                BAAAA               
ABBB                 BAAA                
ABB                  BAA                 
AB                   BA                  
A                    B   
*/
