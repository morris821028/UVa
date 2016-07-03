#include <bits/stdc++.h> 
using namespace std;

struct Info {
	vector<string> url;
	int enable;
	int MX;
	string redirect;
};

vector<string> parseDomain(string s) {
	vector<string> ret;
	for (int i = 0; i < s.length(); i++)
		if (s[i] == '.')
			s[i] = ' ';
	stringstream sin(s);
	while (sin >> s)
		ret.push_back(s);
	return ret;
}
int match(vector<string> &ua, vector<string> &ub) {
	int i = (int) ua.size()-1;
	int j = (int) ub.size()-1;
	for (; i >= 0 && j >= 0; i--, j--) {
		if (ua[i] == "*" || ub[j] == "*")
			return 1;
		if (ua[i] != ub[j])
			return 0;
	}
	return i == -1 && j == -1;
}
int main() {
	int N;
	while (cin >> N) {
		cin.ignore(100, '\n');
			
		string prevURL = "";
		vector<Info> D;
		
		for (int i = 0; i < N; i++) {
			string line, a, b;
			int MX;
			vector<string> args;
			
			getline(cin, line);
			stringstream sin(line);
			while (sin >> line)
				args.push_back(line);
			if (args.size() == 3) {
				sscanf(args[1].c_str(), "%d", &MX);
				a = args[0], b = args[2];
			} else {
				sscanf(args[0].c_str(), "%d", &MX);
				a = prevURL, b = args[1];
			}
			Info u;
			u.url = parseDomain(a);
			u.enable = 1, u.MX = MX, u.redirect = b;
			D.push_back(u);
			prevURL = a;
		}
				
		string cmd, url;
		while (cin >> cmd) {
			if (cmd == "X")
				break;
			cin >> url;
			if (cmd == "A") {
				string next = "";
				int mn_MX;
				vector<string> durl = parseDomain(url);
				for (int i = 0; i < N; i++) {
					if (!D[i].enable)
						continue;
					if (match(D[i].url, durl)) {
						if (next == "" || D[i].MX < mn_MX) {
							mn_MX = D[i].MX;
							next = D[i].redirect;
						}
					}
				}
				
				if (next == "")
					cout << url << " =>" << endl;
				else
					cout << url << " => "<< next << endl;
			} else if (cmd == "D") {
				for (int i = 0; i < N; i++)
					if (D[i].redirect == url)
						D[i].enable = 0;
			} else if (cmd == "U") {
				for (int i = 0; i < N; i++)
					if (D[i].redirect == url)
						D[i].enable = 1;
			}
		}
	}
	return 0;
}
