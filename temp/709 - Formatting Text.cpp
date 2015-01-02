#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
char line[32767];
int dp[32767], dpline[32767], from[32767], N;
vector<string> words;

void printText(int r) {
	int l = from[r];
	if (l > 0)
		printText(l);
	
	if (l == r - 1) {
		puts(words[l].c_str());
		return;
	}
	
	int sum = 0;
	for (int i = l; i < r; i++)
		sum += words[i].length();
	int ngap = r - l - 1, small, large;
	int sn, ln;
	small = large = (N - sum) / ngap;
	sn = ngap, ln = 0;
	if ((N - sum)%ngap)
		large++, ln = (N - sum)%ngap, sn -= ln;
	
	for (int i = l, j = 0; i < r; i++, j++) {
		printf("%s", words[i].c_str());
		if (j < sn) {
			for (int k = 0; k < small; k++)
				printf(" ");
		} else if (j < sn + ln) {
			for (int k = 0; k < large; k++)
				printf(" ");
		}
		
	}
	puts("");
}
int main() {
	while (scanf("%d", &N) == 1 && N) {
		while (getchar() != '\n');
		
		words.clear();
		while (gets(line) && line[0] != '\0') {
			stringstream sin(line);
			string w;
			while (sin >> w)	words.push_back(w); 
		}
		
		memset(dp, 63, sizeof(dp));
		memset(dpline, 63, sizeof(dpline));
		int n = words.size();
		dp[0] = 0, from[0] = -1, dpline[0] = 0;
		for (int i = 0; i < n; i++) {
			if (dp[i] + 500 < dp[i+1] || (dp[i] + 500 == dp[i+1] && dpline[i]+1 <= dpline[i+1])) {
				dp[i+1] = min(dp[i+1], dp[i] + 500);
				from[i+1] = i;
				dpline[i+1] = dpline[i]+1;
			}
			int sum = words[i].length();
			for (int j = i + 1; j < n; j++) {
				sum += words[j].length();
				if (sum + j - i > N)	break;
				int ngap = j - i, small, large;
				int sn, ln;
				small = large = (N - sum) / ngap;
				sn = ngap, ln = 0;
				if ((N - sum)%ngap)
					large++, ln = (N - sum)%ngap, sn -= ln;
				int bad = (small-1)*(small-1)*sn + (large-1)*(large-1)*ln;
				
				if (dp[j+1] > dp[i] + bad || (dp[j+1] == dp[i] + bad && dpline[i]+1 <= dpline[j+1])) {
					dp[j+1] = min(dp[j+1], dp[i] + bad);
					from[j+1] = i;
					dpline[j+1] = dpline[i]+1;
				}
			}
		}
		printText(n);
//		for (int i = 0; i <= n; i++)
//			printf("bad %4d from %4d line %4d\n", dp[i], from[i], dpline[i]);
//		printf("%d\n", dp[n]);
		puts("");
	}
	return 0;
}
/*
28
This is the example you are
actually considering.

25
Writing e-mails is fun, and with this program,
they even look nice.

5
La la la

0
*/
