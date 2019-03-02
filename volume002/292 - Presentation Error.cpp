#include <bits/stdc++.h> 
using namespace std;

string rtrim(char buf[]) {
	int len = strlen(buf);
	for (int i = len-1; i >= 0; i--) {
		if (isspace(buf[i]))
			buf[i] = '\0';
		else
			break;
	}
	return buf;
}

vector<string> read(int n) {
	char buf[65536];
	vector<string> ret;
	for (int i = 0; i < n; i++) {
		fgets(buf, 65536, stdin);
		ret.push_back(rtrim(buf));
	}
	for (int i = ret.size()-1; i >= 0; i--) {
		if (ret[i].length() == 0)
			ret.pop_back();
		else
			break;
	}
	return ret;
}

int strict_line(string gold, string line) {
	int i = 0, j = 0;
	while (i < gold.length() && j < line.length()) {
		if (gold[i] == '[' || gold[i] == ']') {
			i++;
		} else if (gold[i] == line[j]) {
			i++, j++;
		} else {
			return 0;
		}
	}
	if (i < gold.length() && gold[i] == ']')
		i++;
	return i == gold.length() && j == line.length();
}

int strict_diff(vector<string> &gold, vector<string> &file) {
	if (gold.size() != file.size())
		return 0;
	for (int i = 0; i < gold.size(); i++) {
		if (!strict_line(gold[i], file[i]))
			return 0;
	}
	return 1;
}

vector<string> fetch_essential(vector<string> gold) {
	string v = "";
	int in = 0;
	vector<string> E;
	for (auto t : gold) {
		for (int i = 0; i < t.length(); i++)  {
			if (t[i] == '[') {
				in = 1;
				v = "";
			} else if (t[i] == ']') {
				E.push_back(v);
				in = 0;
			} else if (in) {
				v += t[i];
			}
		}
	}
	return E;
}

int loose_diff(vector<string> &gold, vector<string> &file) {
	for (auto &e : gold)
		transform(e.begin(), e.end(), e.begin(), ::toupper);
	for (auto &e : file)
		transform(e.begin(), e.end(), e.begin(), ::toupper);
	vector<string> E = fetch_essential(gold);
	int a = 0;
	int i, j;
	for (i = 0, j = 0; j < E.size() && i < file.size();) {
		int valid = 0;
//		printf("%s\n", E[j].c_str());
		for (; a < file[i].length(); a++) {
			int same = 1;
			for (int k = 0; k < E[j].length(); k++) {
				if (!(a+k < file[i].length() && E[j][k] == file[i][a+k])) {
					same = 0;
					break;
				}
			}
			if (same) {
//				printf("match %d %d\n", i, a);
				a = a + E[j].length();
				valid = 1;
				break;
			}
		}
		if (!valid && a >= file[i].length()) {
			i++, a = 0;
			continue;
		}
		if (!valid)
			return 0;
		j++;
	}
	return j == E.size();
}

void judge(vector<string> &gold, vector<string> &file) {
	int ac = strict_diff(gold, file);
	if (ac) {
		puts("Accepted");
		return;
	}
	int pe = loose_diff(gold, file);
	if (pe) {
		puts("Presentation Error");
		return;
	}
	puts("Wrong Answer");
}

int main() {
	int testcase;
	int n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		while (getchar() != '\n');
		vector<string> out1 = read(n);
		vector<string> out2 = read(m);
		judge(out1, out2);
	}
	return 0;
}
/*
10
1 2
Just one [line]?
Just one line?

1 3
Test [aab]
a ab


1 3
Test [aab]
aAab


1 1
Test [aab]
aAb
1 3
Test [aab]
Test aab


1 1
Test [aab][cd]
aAbcd
1 1
Test [aab][ba]
aaba
1 1
Test [aab][ba]
aabba
1 1
[aab][ba]  	
aabba      
2 2
Test [aab][ba]
cd
aaba
cd

5
1 1
  a   
   a	
1 1
  [a]   
   a	
1 1
  [a]   
   A		
1 1
[a b]
a 	b	
1 3
[a] [b]
a

b

*/
