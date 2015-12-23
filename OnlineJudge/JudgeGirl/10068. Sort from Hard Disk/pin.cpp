#include <bits/stdc++.h>
using namespace std;

// $ awk '{ sub("\r$", ""); print }' out.txt > output.txt
char randLetter() {
	if (rand()%2)
		return rand()%26 + 'a';
	return rand()%26 + 'A';
}
int main() {
//	freopen("in.txt", "w", stdout);
    srand(time(NULL));
    int testcase = 1;
    while (testcase--) {
    	FILE *fout = fopen("in.dat", "wb");
    	int n = 1048576*2;
		for (int i = 0; i < n; i++)	 {
			int x = rand() * rand()%1000000000;
//			if (rand()%100 < 80)
//				x = 514;
//			else
//				x = 1028;
			fwrite(&x, sizeof(int), 1, fout);
//			printf("%d\n", x);
		}
	}
    return 0;
}

