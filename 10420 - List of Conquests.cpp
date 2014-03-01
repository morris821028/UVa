#include <iostream>
#include <cstdio>
#include <string.h>
#include <map>
using namespace std;
int main() {
	int n;
	map<string, int> record;
	while(scanf("%d", &n) == 1) {
		string country, tmp;
		while(n--) {
			cin >> country;
			record[country]++;
			getline(cin, tmp);
		}
		for(map<string, int>::iterator i = record.begin(); i != record.end(); i++)
			cout << i->first << " " << i->second << endl;
	}
    return 0;
}
