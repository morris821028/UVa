#include<stdio.h>
#include<string.h>
typedef struct {
	char s[3][3];
	int num;
}G;
G g[1024];
void solve() {
	int i, x, y, a, b, c;
	int mark[1024], D[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	memset(mark, 0, sizeof(mark));
	mark[g[0].num] = 1;
	for(i = 0; i < 1024; i++) {
		memset(&g[i+1], 0, sizeof(G));
		for(a = 0; a < 3; a++)
			for(b = 0; b < 3; b++) {
				for(c = 0; c < 4; c++) {
					x = a + D[c][0], y = b + D[c][1];
					if(x >= 0 && x < 3 && y >= 0 && y < 3)
						g[i+1].s[a][b] += g[i].s[x][y];
				}
				g[i+1].s[a][b] &= 1;
			}
		for(a = 0, c = 0; a < 3; a++)
			for(b = 0; b < 3; b++)
				g[i+1].num |= g[i+1].s[a][b]<<c, c++;
		if(mark[g[i+1].num])
			break;
		mark[g[i+1].num] = 1;
	}
	printf("%d\n", i-1);
}
int main() {
	int t, i, j, k;
	scanf("%d", &t);
	while(t--) {
		for(i = 0; i < 3; i++) {
			scanf("%s", &g[0].s[i]);
			for(j = 0; j < 3; j++)
				g[0].s[i][j] -= '0';
		}
		for(i = 0, g[0].num = 0, k = 0; i < 3; i++)
			for(j = 0; j < 3; j++)
				g[0].num |= (g[0].s[i][j])<<k, k++;
		solve();
	} 
	return 0;
}
