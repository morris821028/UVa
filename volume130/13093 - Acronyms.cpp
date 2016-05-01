#include <bits/stdc++.h>
using namespace std;

int main() {
	char line[1024];
	while (fgets(line, 1024, stdin)) {
		stringstream sin1(line);
		string b1, b2, x;
		while (sin1 >> x)
			b1 += x[0];
		fgets(line, 1024, stdin);
		stringstream sin2(line);
		while (sin2 >> x)
			b2 += x[0];
		puts(b1 == b2 ? "yes" : "no");
	}
	return 0;
}

