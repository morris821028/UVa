#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <map>
using namespace std;
int main() {
	int t;
	scanf("%d", &t);
	getchar();
	getchar();
	while(t--) {
		map<string, int> record;
		string tree;
		int n = 0;
		while(getline(cin, tree)) {
			if(tree.compare("") == 0)
				break;
			record[tree]++;
			n++;
		}
		for(map<string, int>::iterator i = record.begin(); i != record.end(); i++)
			cout << i->first << " " << fixed << setprecision(4) << i->second*100.0/n << endl;
		if(t)
			puts("");
	}
    return 0;
}
