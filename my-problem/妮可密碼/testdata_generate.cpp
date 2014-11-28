#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;
double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}
main() {
	int n, m, t, a, b, c, tmp;
	int x, y, z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);
	int T = 100;
	while(T--) {
		int n = rand()%5 + 1, slen = 5, starMAX = 3;
		char s[32] = {}, token[32] = {};
		for (int i = 0; i < slen; i++)
			s[i] = '*';
		for (int i = rand()%starMAX; i >= 0; i--)
			s[rand()%slen] = rand()%26 + 'a';
		printf("%d %s\n", n, s);
		for (int i = 0; i < n; i++) {
			int l = rand()%slen, r = rand()%slen, m;
			if (l > r)	swap(l, r);
			m = r - l + 1;
			for (int j = 0, k = l; j < m; j++, k++) {
				if(s[k] == '*')
					token[j] = rand()%26 + 'a';
				else
					token[j] = s[k];
			}
			printf("%s%c", token, i == n - 1 ? '\n' : ' ');
		}
	}
	T = 20;
	while(T--) {
		int n = rand()%20 + 1, slen = 100, starMAX = 70;
		char s[128] = {}, token[128] = {};
		for (int i = 0; i < slen; i++)
			s[i] = '*';
		for (int i = rand()%(slen - starMAX); i >= 0; i--)
			s[i] = rand()%26 + 'a';
		for (int i = 0; i < 500; i++)
			swap(s[rand()%slen], s[rand()%slen]);
		printf("%d %s\n", n, s);
		for (int i = 0; i < n; i++) {
			int l = rand()%slen, r = rand()%slen, m;
			if (l > r)	swap(l, r);
			if (r - l + 1 > 5) 
				r = l + 4;
			m = r - l + 1;
			for (int j = 0, k = l; j < m; j++, k++) {
				if(s[k] == '*')
					token[j] = rand()%26 + 'a';
				else
					token[j] = s[k];
			}
			printf("%s%c", token, i == n - 1 ? '\n' : ' ');
		}
	}
	T = 20;
	while(T--) {
		int n = rand()%20 + 1, slen = 100, starMAX = 70;
		char s[128] = {}, token[128] = {};
		for (int i = 0; i < slen; i++)
			s[i] = '*';
		for (int i = rand()%(slen - starMAX); i >= 0; i--)
			s[i] = rand()%26 + 'a';
		for (int i = 0; i < 500; i++)
			swap(s[rand()%slen], s[rand()%slen]);
		printf("%d %s\n", n, s);
		for (int i = 0; i < n; i++) {
			int l = rand()%slen, r = rand()%slen, m;
			if (l > r)	swap(l, r);
			if (r - l + 1 > 20) 
				r = l + 19;
			m = r - l + 1;
			for (int j = 0, k = l; j < m; j++, k++) {
				if(s[k] == '*')
					token[j] = rand()%26 + 'a';
				else
					token[j] = s[k];
			}
			printf("%s%c", token, i == n - 1 ? '\n' : ' ');
		}
	}
	return 0;
}
