#include <bits/stdc++.h>
using namespace std;

string morse[] = {
	".-",  "-...", "-.-.",  "-..",
	".",  "..-.", "--.", "....",
	"..", ".---", "-.-", ".-..",
	"--", "-.", "---", ".--.",
	"--.-", ".-.", "...", "-",
	"..-", "...-", ".--", "-..-",
	"-.--", "--.."
};
int main() {
	map<string, char> R;
	for (int i = 0; i < 26; i++)
		R[morse[i]] = i+'A';
	int testcase;
	string line;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		getline(cin, line);
		stringstream sin(line);
		while (sin >> line)
			putchar(R[line]);
		puts("");
	}
	return 0;
}