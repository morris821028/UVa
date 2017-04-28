#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 10000000;
	{
		int pos = 0;
		for (; pos < n; ) {
			int sp = rand()%500+1;
			for (; sp; sp--, pos++)
				putchar(' ');
			int cp = rand()%500+1;
			for (; cp && pos < n; cp--, pos++)
				putchar('a'+rand()%26);
		}
		puts("");
	}
	return 0;
}
