#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	char cmd[16], name[16];
	stack<string> path;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", cmd);

		if (cmd[0] == 'S') { // Sleep
			scanf("%s", name);
			path.push(name);
		} else if (cmd[0] == 'K') {	// Kick
			if (!path.empty())
				path.pop();
		} else {	// Test
			if (path.empty())
				puts("Not in a dream");
			else
				printf("%s\n", path.top().c_str());
		}
	}
	return 0;
}

