#include <bits/stdc++.h> 
using namespace std;

int readCmd(int &cmd) {
	static char s[1024], token[1024];
	if (gets(s)) {
		sscanf(s, "%*s %s", token);
		if (!strcmp(token, "SPAM"))
			cmd = 0;
		if (!strcmp(token, "HAM"))
			cmd = 1;
		if (!strcmp(token, "CLASSIFY"))
			cmd = 2;
		return 1;
	} else {
		return 0;
	}
}
vector<string> readPara() {
	static char s[1024];
	vector<string> msg;
	while (gets(s)) {
		if (!strcmp(s, "=="))
			break;
		stringstream sin(s);
		string token;
		while (sin >> token) {
			for (int i = 0; i < token.length(); i++)
				if (isupper(token[i]))
					token[i] = tolower(token[i]);
			msg.push_back(token);
		}
	}
	return msg;
}

class Stat {
public:
	map<string, int> S, H;
	int Scnt, Hcnt;
	Stat() {
		Scnt = Hcnt = 0;
	}
	void insert(vector<string> &v, int kind) {
		for (auto&x : v) {
			if (kind == 0)
				S[x]++, Scnt++;
			else
				H[x]++, Hcnt++;
		}
//		Scnt+=kind == 0, Hcnt+=kind==1;
//		Scnt = S.size(), Hcnt = H.size();
	}
	double computeWS(const string &w) {
		if (S.count(w))
			return (double) S[w] / Scnt;
		return 0;
	}
	double computeWH(const string &w) {
		if (H.count(w))
			return (double) H[w] / Hcnt;
		return 0;
	}
	void classify(vector<string> &v) {
		double a = 1, b = 1, c = 1;
		for (auto&x : v) {
			double d, p, q;
			p = computeWS(x);
			q = computeWH(x);
			if (p == 0)
				d = 0;
			else
				d = (p) / (p + q);
			if (!S.count(x) && !H.count(x))
				d = 0.4;
			d = max(min(d, 0.99), 0.01);
//			printf("-- %lf %lf %lf\n", d, p, q);
			a = a * d,
			b = b * d,
			c = c * (1 - d);
		}
		double p = a / (b + c);
//		printf("%lf\n", p);
		if (p >= 0.6)
			puts("Spam");
		else if (p <= 0.4)
			puts("Ham");
		else
			puts("Unsure");
	}
} tool;
int main() {
	int cmd;
	while (readCmd(cmd)) {
		vector<string> p = readPara(); 
		if (cmd == 0)
			tool.insert(p, 0);
		else if (cmd == 1)
			tool.insert(p, 1);
		else
			tool.classify(p);
	}
	return 0;
}
/*
MESSAGE SPAM
replica rolex
==
MESSAGE SPAM
replica rolex
==
MESSAGE HAM
Hello all
==
MESSAGE CLASSIFY
Hello replica
==
MESSAGE CLASSIFY
replica rolex and some other things
==
MESSAGE CLASSIFY
abc def ghi jkl all
==
*/
