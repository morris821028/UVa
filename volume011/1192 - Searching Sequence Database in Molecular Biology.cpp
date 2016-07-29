#include <bits/stdc++.h>
using namespace std;

char* read_name() {
	static char buf[65536];
	return fgets(buf, 65536, stdin);
}
char sa[65536], sb[65536];
int edit_dist(const char *a, int la, const char *b, int lb) {
	assert(la < 1024 && lb < 1024);
	static int dp[1024][1024] = {};
	for (int i = 0; i <= la; i++) {
		for (int j = 0; j <= lb; j++)
			dp[i][j] = INT_MIN;
	}
	dp[0][0] = 0;
	for (int i = 0; i < la; i++) {
		for (int j = 0; j < lb; j++) {
			if (dp[i][j] == INT_MIN)
				continue;
			if (a[i] == b[j])
				dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]+5);
			dp[i+1][j] = max(dp[i+1][j], dp[i][j]-7);
			dp[i][j+1] = max(dp[i][j+1], dp[i][j]-7);
			dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]-4);
		}
	}
	return dp[la][lb];
}
int main() {
	read_name();
	fgets(sa, 65536, stdin);
	read_name();
	
	int la = strlen(sa)-1, lb;
	sa[la] = '\0';
	
	vector<string> ret;
	int mxSim = INT_MIN;
	while (read_name()) {
		fgets(sb, 65536, stdin);
		lb = strlen(sb)-1;
		sb[lb] = '\0';
		int t = edit_dist(sa, la, sb, lb);
		if (t > mxSim)
			mxSim = t, ret.clear();
		if (t == mxSim)
			ret.push_back(sb);
//		printf("%d\n", edit_dist(sa, la, sb, lb));
		read_name();
	}
	
	printf("The query sequence is:\n");
	printf("%s\n\n", sa);
	printf("The most similar sequences are:\n");
	
	for (int i = 0; i < ret.size(); i++) {
		printf("\n%s\n", ret[i].c_str());
		printf("The similarity score is: %d\n", mxSim);
	}
	return 0;
}
/*
>query 
ACGGG
 
>seq1 
ACGGT 
 
>seq2 
ACGGGG
 
>seq3 
TCCGGTT
 
>seq4 
TCGGG
 
>seq5 
AACGGG
*/
