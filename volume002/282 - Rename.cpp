#include <bits/stdc++.h>
using namespace std;

void rename(vector<string> &files, string from, string to) {
	cout << "rename " << from << " " << to << endl;
	for (auto s : files) {
		int l = 0, r = s.length()-1;
		int fl = 0, fr = from.length()-1;
		while (l < s.length() && s[l] == from[fl])
			l++, fl++;
		while (r >= 0 && s[r] == from[fr])
			r--, fr--;
		if (from[fl] != '*' || from[fr] != '*' || l-r > 1)
			continue;
		cout << "mv " << s << " ";
		int i;
		for (i = 0; i < to.length() && to[i] != '*'; i++)
			cout << to[i];
		for (; l <= r; l++)
			cout << s[l];
		for (i++; i < to.length(); i++)
			cout << to[i];
		cout << endl;		
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	string token, from, to;
	while (cin >> token) {
		vector<string> files;
		if (token != "end") {
			files.push_back(token);
			while (cin >> token && token != "end")
				files.push_back(token);
		}
		
		while (cin >> token && token != "end") {
			cin >> from >> to;
			rename(files, from, to);
		}
		cout << endl;
	}
	return 0;
}
/*
abFile001.c
abFile001.cxx
abprog001.c
abfile.c
abFile.c
abFileprog.c
end
rename abFile*.c bprog*.cxx
end
acm.c
end
rename ac*.c ib*.cpp
end

*/
