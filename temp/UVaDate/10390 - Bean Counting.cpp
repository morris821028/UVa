#include <bits/stdc++.h> 
using namespace std;

char s[1048576];
int main() {
	int testcase;
	scanf("%d", &testcase);
	while(getchar() != '\n');
	while(getchar() != '\n');
	while (testcase--) {
		gets(s);
		int cnt[256] = {};
		for (int i = 0; s[i]; i++)
			cnt[s[i]]++;
		
		map<string, int> R;
		int totShare = 0, totNum = 0;
		while (gets(s)) {
			if (s[0] == '\0')
				break;
			string name, token;
			int offone = 0, righton = 0;
			name = s[0];
			token = s+2;
			for (int i = 0; i < token.size(); i++) {
				char c = token[i];
				int  v = 0;
				i += 2;
				while (token[i] >= '0' && token[i] <= '9')
					v = v * 10 + token[i] - '0', i++;
				if (cnt[c] == v)
					righton++;
				if (abs(cnt[c] - v) == 1)
					offone++;
				totNum++;
			}
			if (offone + righton)
				R[name] += offone + righton * 2;
			totShare += offone + righton * 2;
		}
		
		for (map<string, int>::iterator it = R.begin();
			it != R.end(); it++) {
			double f = (totNum) / (double) totShare * 2 * it->second;
			printf("%s %.2lf\n", it->first.c_str(), f);
		}
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1

aadddddddddddddddddddddddffffffffffffffffwwwwwwwwwwwwccccalalala
A a:6,c:6
B w:12
C d:25
D d:22,c:4,l:3,f:15
*/
