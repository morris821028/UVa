#include <stdio.h> 
#include <string.h>
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

struct Node {
	string name;
	map<string, string> attr;
	vector<int> son;
	void init() {
		attr.clear();
		son.clear();
	}
};
Node node[32767];
int nodesize;
char s[1024];
void parsingAttr(string line, Node &p) {
	string ign = "<>=", attr, val;
	for (int i = 0; i < line.length(); i++) {
		if (ign.find(line[i]) != string::npos) {
			line[i] = ' ';
		}
	}
	stringstream sin(line);
	sin >> p.name;
	while (sin >> attr >> val) {
		p.attr[attr] = val.substr(1, val.length()-2);
//		cout << attr << "+++" << val << endl;
	}
}
int build(string line) {
	int label = ++nodesize;
	Node &p = node[label];
	p.init();
	parsingAttr(line, p);
	while (gets(s)) {
		if (s[1] == '/')
			break;
		p.son.push_back(build(s));
	}
	return label;
}
int main() {
	int testcase, cases = 0, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		while(getchar() != '\n');
		gets(s);
		nodesize = 0;
		int root = build(s);
		scanf("%d", &m);
		while (getchar() != '\n');
		printf("Case %d:\n", ++cases);
		while(m--) {
			gets(s);
			string ign = ".[]", token;
			for (int i = 0; s[i]; i++) {
				if (ign.find(s[i]) != string::npos) {
					s[i] = ' ';
				}
			}
			stringstream sin(s);
			int pos = root;
			string res = "Undefined";
			sin >> token;
			if (token == node[pos].name) {
				while (sin >> token) {
					if (token[0] == '"') {
						string a = token.substr(1, token.length()-2);
						if (node[pos].attr.find(a) != node[pos].attr.end())
							res = node[pos].attr[a];
						break;
					} else {
						int f = 0;
						for (int i = 0; i < node[pos].son.size(); i++) {
							if (token == node[node[pos].son[i]].name) {
								f = 1;
								pos = node[pos].son[i];
								break;
							}
						}
						if (!f)
							break;
					}
				}
			}
			printf("%s\n", res.c_str());
		} 
	}
	return 0;
}
