#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>
#include <functional>
using namespace std;

vector<int> getLineNumber(char s[]) {
	stringstream sin(s);
	vector<int> ret;
	int x;
	while(sin >> x)
		ret.push_back(x);
	return ret;
}
int main() {
	char s[1024];
	int H;
	while(gets(s)) {
		sscanf(s, "%d", &H);
		vector<int> B, W;
		gets(s), B = getLineNumber(s);
		gets(s), W = getLineNumber(s);
		gets(s);
		sort(B.begin(), B.end(), greater<int>());
		sort(W.begin(), W.end(), greater<int>());
		
		int f = 0;
		for(int i = 0; i < B.size(); i++)
		for(int j = 0; j < W.size(); j++)
		for(int a = i+1; a < B.size(); a++)
		for(int b = j+1; b < W.size(); b++) {
			if(B[i]+W[j]+B[a]+W[b] == H) {
				printf("%d %d %d %d\n", B[i], W[j], B[a], W[b]);
				i = a = B.size();
				j = b = W.size();
				f = 1;
			}
		}
		if(!f)
			puts("no solution");
	}
	return 0;
}
