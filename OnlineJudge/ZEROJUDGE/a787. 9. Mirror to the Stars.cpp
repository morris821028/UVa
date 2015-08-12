#include <bits/stdc++.h> 
using namespace std;

int main() {
	char name[128], cmd[128], g[128][128];
	int W, H;
	while (scanf("%s %d %d %s", name, &W, &H, cmd) == 4) {
		for (int i = 0; i < H; i++)
			scanf("%s", g[i]);				
		for (int i = 0; cmd[i]; i++) {
			if (cmd[i] == 'I') {
				for (int a = 0; a < W; a++)
					for (int p = 0, q = H-1; p < q; p++, q--)
						swap(g[p][a], g[q][a]);
			} else {
				for (int a = 0; a < H; a++)
					for (int p = 0, q = W-1; p < q; p++, q--)
						swap(g[a][p], g[a][q]);
			}
		}
		puts(name);
		for (int i = 0; i < H; i++)
			puts(g[i]);
	}
	return 0;
}
