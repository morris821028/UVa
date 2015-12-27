#include <bits/stdc++.h>
using namespace std;

// $ awk '{ sub("\r$", ""); print }' out.txt > output.txt
char randLetter() {
	if (rand()%2)
		return rand()%26 + 'a';
	return rand()%26 + 'A';
}
char randChar() {
	return rand()%('z' - ' ' + 1) + ' ';
}
int main() {
	freopen("in.txt", "w", stdout);
    srand(time(NULL));
    int testcase = 10;
    while (testcase--) {
    	int R = rand()%50 + 1, N = rand()%8+1;
    	printf("%d %d\n", R, N);
    	int x[16], y[16], z[16];
    	for (int i = 0; i < N; i++) {
    		do {
    			x[i] = rand()%(2*R) - R;
    			y[i] = rand()%(2*R) - R;
    			z[i] = rand()%(2*R) - R;
    			int same = 0;
    			for (int j = 0; j < i; j++)
    				same |= x[i] == x[j] && y[i] == y[j] && z[i] == z[j];
    			if (!same)
    				break;
			} while (true);
			printf("%d %d %d\n", x[i], y[i], z[i]);
		}
		if (testcase)
			puts("");
	}
    return 0;
}

