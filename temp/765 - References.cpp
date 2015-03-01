#include <stdio.h> 
#include <map>
#include <iostream>
#include <string.h>
#include <vector> 
#include <set>
#include <sstream>
using namespace std;
vector<string> para;
map<int, string> ref;
int readParagraph()  {
	string s, p = "";
	while (true) {
		if (!getline(cin, s)) {
			if (p.length())
				break;
			return 0;
		}
		int space = 1;
		for (int i = 0; i < s.length(); i++)
			space &= s[i] == ' ';
		if (space)
			break;
		p += s + "\n";
	}
	if (p.length() == 0)
		return 1;
	if (p[0] == '[') {
		int num = 0, i = 1;
		for (i = 1; p[i] != ']'; i++)
			num = num * 10 + p[i] - '0';
		p = p.substr(i+1);
		ref[num] = p;
	} else {
		para.push_back(p);
	}
	return 1;
}
string replaceAll(string str, string& from, string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
string int2str(int x) {
	string s;
	stringstream sin(s);
	sin << x; 
	return sin.str();
}
int main() {
//	freopen("R02", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	while (readParagraph());
	
	vector<int> order;
	map<int, int> used;
	for (int i = 0; i < para.size(); i++) {
		for (int j = 0; j < para[i].size(); j++) {
			if (para[i][j] == '[') {
				int num = 0;
				for (j++; j < para[i].size() && para[i][j] != ']'; j++)
					num = num * 10 + para[i][j] - '0';
				if (used[num] == 0) {
					if (ref.count(num)) {
						used[num] = order.size() + 1;
						order.push_back(num);
					}
				}
			}
		}
	}
	
	for (int i = 0; i < para.size(); i++) {
		for (int j = 0; j < para[i].size(); j++) {
			if (para[i][j] == '[') {
				int num = 0, start_pos = j + 1, len = 0;
				for (j++; j < para[i].size() && para[i][j] != ']'; j++)
					num = num * 10 + para[i][j] - '0', len ++;
				if (used[num] != 0) {
					string to = int2str(used[num]);
					para[i].replace(start_pos, len, to);
					j = start_pos + len - 2;
				}
			}
		}
	}
	
	for (int i = 0; i < para.size(); i++) {
		if (i)	cout << endl;
		cout << para[i];
	}
	cout << endl;
	for (int i = 0; i < order.size(); i++) {
		cout << "[" << (i+1) << "]";
		cout << ref[order[i]];
		if (i != order.size() - 1)
			cout << endl;
	}
	return 0;
}
/*
*/
