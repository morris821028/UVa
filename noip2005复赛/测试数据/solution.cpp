#include <iostream>
#include <cassert>
#include <string>

using namespace std;

int main() {
	int n;
	cin >> n;
	assert(1 <= n && n <= 100);
	string output;
	int value = -1;
	int i;
	int all = 0;
	for (i = 0; i < n; i++) {
		string str;
		int a, b;
		char x, y;
		int p;
		cin >> str >> a >> b >> x >> y >> p;
		assert(0 <= a && a <= 100);
		assert(0 <= b && b <= 100);
		assert(0 <= p && p <= 10);
		assert(x == 'Y' || x == 'N');
		assert(y == 'Y' || y == 'N');
		assert(str.length() <= 20);
		for (int q = 0; q < str.length(); q++) {
			assert(isalpha(str[q]));
		}
		int total = 0;
		if (a > 80 && p >= 1) total += 8000;
		if (a > 85 && b > 80) total += 4000;
		if (a > 90) total += 2000;
		if (a > 85 && y == 'Y') total += 1000;
		if (b > 80 && x == 'Y') total += 850;
		if (total > value) {
			value = total;
			output = str;
		}
		all += total;
	}
	assert(value > 0);
	cout << output << endl;
	cout << value << endl;
	cout << all << endl;
	{char c;assert(!(cin >> c));}
}
